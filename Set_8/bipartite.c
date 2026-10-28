#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];

int n;


/* Check whether graph is bipartite */
int isBipartite()
{
    int queue[MAX];

    int front, rear;
    int i, j;

    /* -1 means uncolored */
    for(i = 0; i < n; i++)
        color[i] = -1;

    /*
     * We need to check every vertex because
     * the graph may be disconnected.
     */
    for(i = 0; i < n; i++)
    {
        if(color[i] != -1)
            continue;

        front = 0;
        rear = 0;

        /* Start with color 0 */
        color[i] = 0;
        queue[rear++] = i;

        while(front < rear)
        {
            int current = queue[front++];

            for(j = 0; j < n; j++)
            {
                if(graph[current][j])
                {
                    /*
                     * If adjacent vertex is not colored,
                     * give it the opposite color.
                     */
                    if(color[j] == -1)
                    {
                        color[j] = 1 - color[current];

                        queue[rear++] = j;
                    }

                    /*
                     * Same color on adjacent vertices
                     * means graph is not bipartite.
                     */
                    else if(color[j] == color[current])
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}


int main()
{
    int i, j;

    printf("========================================\n");
    printf("          BIPARTITE GRAPH TEST\n");
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

    if(isBipartite())
    {
        printf("\nThe graph is BIPARTITE.\n");

        printf("\nTwo groups are:\n");

        printf("Group 1: ");

        for(i = 0; i < n; i++)
        {
            if(color[i] == 0)
                printf("%d ", i);
        }

        printf("\nGroup 2: ");

        for(i = 0; i < n; i++)
        {
            if(color[i] == 1)
                printf("%d ", i);
        }

        printf("\n");
    }
    else
    {
        printf("\nThe graph is NOT BIPARTITE.\n");
        printf("An edge connects two vertices having the same color.\n");
    }

    printf("\n========================================\n");

    return 0;
}