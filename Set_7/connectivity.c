#include <stdio.h>

#define MAX 20
#define MAX_EDGES 200

int graph[MAX][MAX];
int n;

/* DFS information */
int visited[MAX];
int disc[MAX];
int low[MAX];
int parent[MAX];
int timer;

/* Articulation point information */
int articulation[MAX];

/* Stack used to store edges of Biconnected Components */
struct Edge
{
    int u;
    int v;
};

struct Edge stack[MAX_EDGES];
int top = -1;


/* ------------------------------------------------ */
/* Find Connected Components using DFS              */
/* ------------------------------------------------ */

void DFS_Connected(int u)
{
    int v;

    visited[u] = 1;
    printf("%d ", u);

    for(v = 0; v < n; v++)
    {
        if(graph[u][v] && !visited[v])
        {
            DFS_Connected(v);
        }
    }
}

void connectedComponents()
{
    int i;
    int count = 0;

    for(i = 0; i < n; i++)
        visited[i] = 0;

    for(i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            count++;

            printf("Component %d: ", count);

            DFS_Connected(i);

            printf("\n");
        }
    }
}


/* ------------------------------------------------ */
/* Print one Biconnected Component                  */
/* ------------------------------------------------ */

void printBiconnectedComponent(int u, int v)
{
    struct Edge e;

    printf("Biconnected Component: ");

    while(top >= 0)
    {
        e = stack[top--];

        printf("(%d-%d) ", e.u, e.v);

        if(e.u == u && e.v == v)
            break;
    }

    printf("\n");
}


/* ------------------------------------------------ */
/* DFS for BCC, Articulation Points and Bridges     */
/* ------------------------------------------------ */

void DFS(int u)
{
    int v;
    int children = 0;

    visited[u] = 1;

    disc[u] = low[u] = ++timer;

    for(v = 0; v < n; v++)
    {
        if(!graph[u][v])
            continue;


        /* ---------------------------------------- */
        /* Tree Edge                                */
        /* ---------------------------------------- */

        if(!visited[v])
        {
            children++;

            parent[v] = u;

            /* Push edge onto stack */
            stack[++top].u = u;
            stack[top].v = v;

            DFS(v);

            /* Update low value */
            if(low[v] < low[u])
                low[u] = low[v];


            /* ------------------------------------ */
            /* Check Articulation Point              */
            /* ------------------------------------ */

            /* DFS root */
            if(parent[u] == -1 && children > 1)
                articulation[u] = 1;

            /* Non-root vertex */
            if(parent[u] != -1 && low[v] >= disc[u])
                articulation[u] = 1;


            /* ------------------------------------ */
            /* Check Bridge                         */
            /* ------------------------------------ */

            if(low[v] > disc[u])
            {
                printf("Bridge: %d - %d\n", u, v);
            }


            /* ------------------------------------ */
            /* Check Biconnected Component          */
            /* ------------------------------------ */

            if(low[v] >= disc[u])
            {
                printBiconnectedComponent(u, v);
            }
        }


        /* ---------------------------------------- */
        /* Back Edge                                */
        /* ---------------------------------------- */

        else if(v != parent[u] && disc[v] < disc[u])
        {
            stack[++top].u = u;
            stack[top].v = v;

            if(disc[v] < low[u])
                low[u] = disc[v];
        }
    }
}


/* ------------------------------------------------ */
/* Find all required information                    */
/* ------------------------------------------------ */

void findBiconnectedInformation()
{
    int i;

    for(i = 0; i < n; i++)
    {
        visited[i] = 0;
        disc[i] = 0;
        low[i] = 0;
        parent[i] = -1;
        articulation[i] = 0;
    }

    timer = 0;
    top = -1;

    for(i = 0; i < n; i++)
    {
        if(!visited[i])
        {
            DFS(i);

            /*
             * Any remaining edges belong to
             * one final biconnected component.
             */
            if(top != -1)
            {
                printf("Biconnected Component: ");

                while(top >= 0)
                {
                    printf("(%d-%d) ",
                           stack[top].u,
                           stack[top].v);

                    top--;
                }

                printf("\n");
            }
        }
    }

    /* -------------------------------------------- */
    /* Print Articulation Points                    */
    /* -------------------------------------------- */

    printf("\nArticulation Points:\n");

    int found = 0;

    for(i = 0; i < n; i++)
    {
        if(articulation[i])
        {
            printf("%d ", i);
            found = 1;
        }
    }

    if(!found)
        printf("None");

    printf("\n");
}


/* ------------------------------------------------ */
/* Main                                             */
/* ------------------------------------------------ */

int main()
{
    int i, j;

    printf("========================================\n");
    printf(" GRAPH CONNECTIVITY ANALYSIS\n");
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
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nConnected Components:\n");
    printf("----------------------------------------\n");

    connectedComponents();

    printf("\nBiconnected Components and Bridges:\n");
    printf("----------------------------------------\n");

    findBiconnectedInformation();

    printf("\n========================================\n");

    return 0;
}