#include <stdio.h>

#define V 6

int graph[V][V] =
{
    {0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0, 0}
};

int visited[V];
int path[V];
int pathLength;

int minCycle = V + 1;
int maxCycle = 0;

void findCycles(int start, int current)
{
    visited[current] = 1;
    path[pathLength++] = current;

    for (int next = 0; next < V; next++)
    {
        if (!graph[current][next])
            continue;

        if (next == start && pathLength >= 2)
        {
            if (pathLength < minCycle)
                minCycle = pathLength;

            if (pathLength > maxCycle)
                maxCycle = pathLength;
        }
        else if (!visited[next] && next >= start)
        {
            findCycles(start, next);
        }
    }

    pathLength--;
    visited[current] = 0;
}

void findSmallestLargestCycle()
{
    for (int start = 0; start < V; start++)
    {
        for (int i = 0; i < V; i++)
            visited[i] = 0;

        pathLength = 0;

        findCycles(start, start);
    }

    if (maxCycle == 0)
    {
        printf("No cycle exists.\n");
    }
    else
    {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }
}

int main()
{
    findSmallestLargestCycle();

    return 0;
}