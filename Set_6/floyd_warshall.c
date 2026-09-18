#include <stdio.h>

#define V 4
#define INF 9999

void floydWarshall(int graph[V][V])
{
    int distance[V][V];

    /* Copy graph into distance matrix */
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            distance[i][j] = graph[i][j];
    }

    printf("Initial distance matrix:\n");

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (distance[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", distance[i][j]);
        }
        printf("\n");
    }

    /* Dynamic programming */
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (distance[i][k] != INF &&
                    distance[k][j] != INF &&
                    distance[i][k] + distance[k][j] < distance[i][j])
                {
                    distance[i][j] =
                        distance[i][k] + distance[k][j];
                }
            }
        }
    }

    printf("\nFinal all-pairs shortest-path matrix:\n");

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (distance[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", distance[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int graph[V][V] =
    {
        {0,   5,  INF, 10},
        {INF, 0,   3,  INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    printf("========== FLOYD-WARSHALL ALGORITHM ==========\n\n");

    floydWarshall(graph);

    return 0;
}