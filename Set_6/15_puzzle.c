#include <stdio.h>
#include <stdlib.h>

#define N 4
#define SIZE 16

struct Node
{
    int board[SIZE];
    int blank;
    int level;
    int cost;
    struct Node *parent;
};

int goal[SIZE] =
{
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 0
};

int manhattan(int board[])
{
    int distance = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] == 0)
            continue;

        int target = board[i] - 1;

        int currentRow = i / N;
        int currentCol = i % N;

        int targetRow = target / N;
        int targetCol = target % N;

        distance += abs(currentRow - targetRow)
                  + abs(currentCol - targetCol);
    }

    return distance;
}

struct Node *createNode(int board[], int blank,
                        int level, struct Node *parent)
{
    struct Node *node = malloc(sizeof(struct Node));

    for (int i = 0; i < SIZE; i++)
        node->board[i] = board[i];

    node->blank = blank;
    node->level = level;
    node->parent = parent;

    /*
       Branch and bound cost:
       f(n) = g(n) + h(n)

       g(n) = level/depth
       h(n) = Manhattan distance
    */
    node->cost = level + manhattan(board);

    return node;
}

void printBoard(int board[])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] == 0)
            printf("   _");
        else
            printf("%4d", board[i]);

        if ((i + 1) % N == 0)
            printf("\n");
    }

    printf("\n");
}

int isGoal(int board[])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i] != goal[i])
            return 0;
    }

    return 1;
}

int isSame(int a[], int b[])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (a[i] != b[i])
            return 0;
    }

    return 1;
}

struct Node *findBest(struct Node *list[], int count)
{
    int best = 0;

    for (int i = 1; i < count; i++)
    {
        if (list[i]->cost < list[best]->cost)
            best = i;
    }

    struct Node *result = list[best];

    for (int i = best; i < count - 1; i++)
        list[i] = list[i + 1];

    return result;
}

void printSolution(struct Node *node)
{
    if (node == NULL)
        return;

    printSolution(node->parent);

    printf("Move level %d | Cost = %d\n",
           node->level, node->cost);

    printBoard(node->board);
}

int main()
{
    /*
       Starting puzzle:

       1  2  3  4
       5  6  7  8
       9 10  11 12
       13 14 _ 15

       Solution:
       Move blank right.
    */

    int start[SIZE] =
    {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 0, 15
    };

    struct Node *open[10000];
    int openCount = 0;

    int visited[10000][SIZE];
    int visitedCount = 0;

    int blank = 14;

    struct Node *root =
        createNode(start, blank, 0, NULL);

    open[openCount++] = root;

    struct Node *solution = NULL;

    int rowMove[] = {-1, 1, 0, 0};
    int colMove[] = {0, 0, -1, 1};

    printf("========== 15-PUZZLE USING BRANCH AND BOUND ==========\n\n");

    printf("Initial puzzle:\n");
    printBoard(start);

    while (openCount > 0)
    {
        struct Node *current =
            findBest(open, openCount--);

        if (isGoal(current->board))
        {
            solution = current;
            break;
        }

        for (int i = 0; i < SIZE; i++)
            visited[visitedCount][i] = current->board[i];

        visitedCount++;

        int r = current->blank / N;
        int c = current->blank % N;

        for (int move = 0; move < 4; move++)
        {
            int nr = r + rowMove[move];
            int nc = c + colMove[move];

            if (nr < 0 || nr >= N ||
                nc < 0 || nc >= N)
                continue;

            int newBlank = nr * N + nc;

            int newBoard[SIZE];

            for (int j = 0; j < SIZE; j++)
                newBoard[j] = current->board[j];

            newBoard[current->blank] =
                newBoard[newBlank];

            newBoard[newBlank] = 0;

            int alreadyVisited = 0;

            for (int j = 0; j < visitedCount; j++)
            {
                if (isSame(newBoard, visited[j]))
                {
                    alreadyVisited = 1;
                    break;
                }
            }

            if (alreadyVisited)
                continue;

            struct Node *child =
                createNode(newBoard,
                           newBlank,
                           current->level + 1,
                           current);

            open[openCount++] = child;
        }
    }

    if (solution != NULL)
    {
        printf("Solution found!\n\n");
        printf("Solution path:\n");

        printSolution(solution);
    }
    else
    {
        printf("No solution found.\n");
    }

    return 0;
}