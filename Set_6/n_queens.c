#include <stdio.h>

#define N 4

int board[N][N];
int solutionCount = 0;

int isSafe(int row, int col)
{
    /* Check column */
    for (int i = 0; i < row; i++)
    {
        if (board[i][col])
            return 0;
    }

    /* Check upper-left diagonal */
    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--)
    {
        if (board[i][j])
            return 0;
    }

    /* Check upper-right diagonal */
    for (int i = row - 1, j = col + 1;
         i >= 0 && j < N;
         i--, j++)
    {
        if (board[i][j])
            return 0;
    }

    return 1;
}

void printBoard()
{
    solutionCount++;

    printf("\nSolution %d:\n", solutionCount);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j])
                printf(" Q ");
            else
                printf(" . ");
        }

        printf("\n");
    }
}

void solve(int row)
{
    if (row == N)
    {
        printBoard();
        return;
    }

    for (int col = 0; col < N; col++)
    {
        if (isSafe(row, col))
        {
            board[row][col] = 1;

            solve(row + 1);

            /* Backtrack */
            board[row][col] = 0;
        }
    }
}

int main()
{
    printf("========== N-QUEENS USING BACKTRACKING ==========\n");
    printf("Board size: %d x %d\n", N, N);

    solve(0);

    printf("\nTotal solutions = %d\n", solutionCount);

    return 0;
}