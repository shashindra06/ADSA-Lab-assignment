#include <stdio.h>

#define V 6

int graph[V][V] =
{
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};

int state[V];
int entry[V];
int exitTime[V];
int time = 0;

void dfs(int u)
{
    state[u] = 1;
    entry[u] = ++time;

    for (int v = 0; v < V; v++)
    {
        if (!graph[u][v])
            continue;

        if (state[v] == 0)
        {
            printf("%d -> %d : Tree Edge\n", u, v);
            dfs(v);
        }
        else if (state[v] == 1)
        {
            printf("%d -> %d : Back Edge\n", u, v);
        }
        else
        {
            if (entry[u] < entry[v])
                printf("%d -> %d : Forward Edge\n", u, v);
            else
                printf("%d -> %d : Cross Edge\n", u, v);
        }
    }

    state[u] = 2;
    exitTime[u] = ++time;
}

void DFS()
{
    for (int i = 0; i < V; i++)
        state[i] = 0;

    for (int i = 0; i < V; i++)
    {
        if (state[i] == 0)
            dfs(i);
    }
}

int main()
{
    printf("DFS Edge Classification:\n");

    DFS();

    return 0;
}