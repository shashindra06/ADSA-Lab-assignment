#include <stdio.h>

#define V 5
#define INF 9999

void prim(int graph[V][V])
{
    int parent[V];
    int key[V];
    int used[V];

    for (int i = 0; i < V; i++)
    {
        key[i] = INF;
        used[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int min = INF;
        int u = -1;

        for (int i = 0; i < V; i++)
        {
            if (!used[i] && key[i] < min)
            {
                min = key[i];
                u = i;
            }
        }

        used[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] &&
                !used[v] &&
                graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;

    printf("Minimum Spanning Tree:\n");

    for (int i = 1; i < V; i++)
    {
        printf("%d - %d : %d\n",
               parent[i], i, graph[i][parent[i]]);

        total += graph[i][parent[i]];
    }

    printf("Total cost = %d\n", total);
}

int main()
{
    int graph[V][V] =
    {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    prim(graph);

    return 0;
}