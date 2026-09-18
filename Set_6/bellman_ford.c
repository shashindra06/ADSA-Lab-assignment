#include <stdio.h>

#define V 5
#define E 8
#define INF 9999

struct Edge
{
    int source;
    int destination;
    int weight;
};

void bellmanFord(struct Edge edges[], int source)
{
    int distance[V];

    for (int i = 0; i < V; i++)
        distance[i] = INF;

    distance[source] = 0;

    printf("Source vertex: %d\n", source);
    printf("Relaxing all edges %d times...\n\n", V - 1);

    for (int i = 1; i <= V - 1; i++)
    {
        int changed = 0;

        for (int j = 0; j < E; j++)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int w = edges[j].weight;

            if (distance[u] != INF &&
                distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                changed = 1;
            }
        }

        printf("After iteration %d: ", i);

        for (int j = 0; j < V; j++)
        {
            if (distance[j] == INF)
                printf("INF ");
            else
                printf("%d ", distance[j]);
        }

        printf("\n");

        if (!changed)
        {
            printf("\nNo more distance updates needed.\n");
            break;
        }
    }

    /* Check for negative-weight cycle */
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;
        int w = edges[i].weight;

        if (distance[u] != INF &&
            distance[u] + w < distance[v])
        {
            printf("\nNegative-weight cycle detected.\n");
            return;
        }
    }

    printf("\nFinal shortest distances from vertex %d:\n", source);

    for (int i = 0; i < V; i++)
    {
        if (distance[i] == INF)
            printf("%d -> %d : INF (unreachable)\n", source, i);
        else
            printf("%d -> %d : %d\n", source, i, distance[i]);
    }
}

int main()
{
    struct Edge edges[E] =
    {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {1, 4, -4},
        {2, 3, -3},
        {2, 4, 9},
        {3, 1, -2}
    };

    printf("========== BELLMAN-FORD ALGORITHM ==========\n\n");

    bellmanFord(edges, 0);

    return 0;
}