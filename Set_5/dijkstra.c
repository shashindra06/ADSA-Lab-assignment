#include <stdio.h>

#define V 5
#define INF 9999

void dijkstra(int graph[V][V], int source)
{
    int distance[V];
    int visited[V];

    for (int i = 0; i < V; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[source] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int min = INF;
        int u = -1;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && distance[i] < min)
            {
                min = distance[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] != 0 &&
                distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", source);

    for (int i = 0; i < V; i++)
        printf("%d -> %d = %d\n", source, i, distance[i]);
}

int main()
{
    int graph[V][V] =
    {
        {0, 10, 3, 0, 0},
        {10, 0, 1, 2, 0},
        {3, 1, 0, 8, 2},
        {0, 2, 8, 0, 7},
        {0, 0, 2, 7, 0}
    };

    dijkstra(graph, 0);

    return 0;
}