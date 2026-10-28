#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int n;

int path[MAX];


/* Check whether vertex can be added */
int isSafe(int vertex, int position)
{
    int i;

    /* Must be connected to previous vertex */
    if(graph[path[position - 1]][vertex] == 0)
        return 0;

    /* Vertex must not already be in path */
    for(i = 0; i < position; i++)
    {
        if(path[i] == vertex)
            return 0;
    }

    return 1;
}


/* Hamiltonian cycle using backtracking */
int hamiltonianCycle(int position)
{
    int vertex;

    /* All vertices included */
    if(position == n)
    {
        /*
         * Check whether last vertex connects
         * back to starting vertex.
         */
        if(graph[path[n - 1]][path[0]])
            return 1;

        return 0;
    }

    /*
     * Try every vertex except the starting vertex.
     */
    for(vertex = 1; vertex < n; vertex++)
    {
        if(isSafe(vertex, position))
        {
            path[position] = vertex;

            if(hamiltonianCycle(position + 1))
                return 1;

            /* Backtrack */
            path[position] = -1;
        }
    }

    return 0;
}


int main()
{
    int i, j;

    printf("========================================\n");
    printf("        HAMILTONIAN CYCLE\n");
    printf("========================================\n");

    printf("\nEnter number of vertices: ");
    scanf("%d", &n);

    if(n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 0;
    }

    printf("\nEnter adjacency matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    }

    for(i = 0; i < n; i++)
        path[i] = -1;

    /*
     * Start from vertex 0.
     */
    path[0] = 0;

    if(hamiltonianCycle(1))
    {
        printf("\nHamiltonian Cycle exists.\n");

        printf("Cycle: ");

        for(i = 0; i < n; i++)
            printf("%d -> ", path[i]);

        printf("0\n");
    }
    else
    {
        printf("\nNo Hamiltonian Cycle exists.\n");
    }

    printf("\n========================================\n");

    return 0;
}