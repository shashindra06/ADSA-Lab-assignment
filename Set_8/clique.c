#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int n, m;

int clique[MAX];

/* Check whether vertex can be added */
int isSafe(int vertex, int position)
{
    int i;

    for(i = 0; i < position; i++)
    {
        if(graph[clique[i]][vertex] == 0)
            return 0;
    }

    return 1;
}


/* Find clique using backtracking */
int findClique(int vertex, int position)
{
    int i;

    /* Required clique size reached */
    if(position == m)
        return 1;

    /* Not enough vertices remaining */
    if(vertex >= n)
        return 0;

    for(i = vertex; i < n; i++)
    {
        if(isSafe(i, position))
        {
            clique[position] = i;

            if(findClique(i + 1, position + 1))
                return 1;
        }
    }

    return 0;
}


int main()
{
    int i, j;

    printf("========================================\n");
    printf("          CLIQUE DETECTION\n");
    printf("========================================\n");

    printf("\nEnter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    int e;
    scanf("%d", &e);

    if(n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 0;
    }

    if(m <= 0 || m > n)
    {
        /* m will be entered below */
    }

    printf("Enter size of clique to find: ");
    scanf("%d", &m);

    if(m <= 0 || m > n)
    {
        printf("\nInvalid clique size.\n");
        return 0;
    }

    /* Initialize graph */
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            graph[i][j] = 0;
    }

    printf("\nEnter %d edges (u v):\n", e);

    for(i = 0; i < e; i++)
    {
        int u, v;

        scanf("%d %d", &u, &v);

        if(u >= 0 && u < n && v >= 0 && v < n && u != v)
        {
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
    }

    if(findClique(0, 0))
    {
        printf("\nClique of size %d exists.\n", m);

        printf("Clique vertices: ");

        for(i = 0; i < m; i++)
            printf("%d ", clique[i]);

        printf("\n");
    }
    else
    {
        printf("\nNo clique of size %d exists.\n", m);
    }

    printf("\n========================================\n");

    return 0;
}

// Enter number of vertices: 5
// Enter number of edges: 6
// Enter size of clique to find: 3

// Enter 6 edges (u v):
// 0 1
// 0 2
// 1 2
// 1 3
// 2 3
// 3 4
