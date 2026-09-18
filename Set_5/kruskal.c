#include <stdio.h>

#define V 5
#define E 7

struct Edge
{
    int u;
    int v;
    int weight;
};

int parent[V];

int find(int x)
{
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a != b)
        parent[b] = a;
}

void sortEdges(struct Edge edges[])
{
    for (int i = 0; i < E - 1; i++)
    {
        for (int j = 0; j < E - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal(struct Edge edges[])
{
    sortEdges(edges);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int count = 0;
    int total = 0;

    printf("Minimum Spanning Tree:\n");

    for (int i = 0; i < E && count < V - 1; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u) != find(v))
        {
            printf("%d - %d : %d\n",
                   u, v, edges[i].weight);

            total += edges[i].weight;
            unionSet(u, v);
            count++;
        }
    }

    printf("Total cost = %d\n", total);
}

int main()
{
    struct Edge edges[E] =
    {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    kruskal(edges);

    return 0;
}