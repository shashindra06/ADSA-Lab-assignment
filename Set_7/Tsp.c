#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX 100
#define INF 1000000000

int n;
int graph[MAX][MAX];

int visited[MAX];
int minCost;

/* ------------------------------------------------ */
/* Find minimum edge leaving each city              */
/* Used for a simple lower bound                    */
/* ------------------------------------------------ */

int minOutgoing[MAX];


/* ------------------------------------------------ */
/* TSP using Backtracking + Branch and Bound        */
/* ------------------------------------------------ */

void tsp(int city, int count, int currentCost)
{
    int next;

    /* All cities visited */
    if(count == n)
    {
        if(graph[city][0] != 0)
        {
            int totalCost;

            totalCost = currentCost + graph[city][0];

            if(totalCost < minCost)
                minCost = totalCost;
        }

        return;
    }


    /*
     * Simple lower bound.
     *
     * Every remaining city will need at least
     * its minimum outgoing edge.
     */
    int lowerBound = currentCost;

    for(next = 0; next < n; next++)
    {
        if(!visited[next])
            lowerBound += minOutgoing[next];
    }

    /*
     * If even the lower bound is already worse
     * than the best solution, stop exploring.
     */
    if(lowerBound >= minCost)
        return;


    /* Try every unvisited city */
    for(next = 0; next < n; next++)
    {
        if(!visited[next] && graph[city][next] != 0)
        {
            int newCost;

            newCost = currentCost + graph[city][next];

            /*
             * No need to continue if current cost
             * already exceeds the best solution.
             */
            if(newCost >= minCost)
                continue;

            visited[next] = 1;

            tsp(next, count + 1, newCost);

            visited[next] = 0;
        }
    }
}


/* ------------------------------------------------ */
/* Solve TSP                                        */
/* ------------------------------------------------ */

int solveTSP()
{
    int i;

    minCost = INF;

    for(i = 0; i < n; i++)
        visited[i] = 0;

    /*
     * Calculate minimum outgoing edge
     * for every city.
     */
    for(i = 0; i < n; i++)
    {
        minOutgoing[i] = INF;

        int j;

        for(j = 0; j < n; j++)
        {
            if(i != j && graph[i][j] < minOutgoing[i])
            {
                minOutgoing[i] = graph[i][j];
            }
        }
    }

    visited[0] = 1;

    tsp(0, 1, 0);

    return minCost;
}


/* ------------------------------------------------ */
/* Generate a symmetric weighted graph              */
/* ------------------------------------------------ */

void generateGraph(int size)
{
    int i, j;

    n = size;

    for(i = 0; i < n; i++)
    {
        graph[i][i] = 0;

        for(j = i + 1; j < n; j++)
        {
            int cost;

            cost = rand() % 100 + 1;

            graph[i][j] = cost;
            graph[j][i] = cost;
        }
    }
}


/* ------------------------------------------------ */
/* Measure execution time                           */
/* ------------------------------------------------ */

void measureTime(int sizes[], int count)
{
    int i;

    printf("\n========================================\n");
    printf("       TSP EXECUTION TIME ANALYSIS\n");
    printf("========================================\n");

    printf("\nProblem Size\tExecution Time\tStatus\n");
    printf("-----------------------------------------------\n");

    for(i = 0; i < count; i++)
    {
        clock_t start;
        clock_t end;

        double timeTaken;

        int result;

        generateGraph(sizes[i]);

        /*
         * Exact TSP becomes impractical very quickly.
         *
         * We actually execute the smaller cases.
         * For very large cases, we don't freeze
         * the computer.
         */
        if(sizes[i] > 12)
        {
            printf("%d\t\t-\t\tToo large for exact TSP\n",
                   sizes[i]);

            continue;
        }

        start = clock();

        result = solveTSP();

        end = clock();

        timeTaken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.6f sec\tCompleted\n",
               sizes[i], timeTaken);

        printf("Minimum tour cost = %d\n", result);
    }

    printf("-----------------------------------------------\n");
}


/* ------------------------------------------------ */
/* Main                                             */
/* ------------------------------------------------ */

int main()
{
    /*
     * Required sizes from the assignment.
     */
    int sizes[] = {10, 20, 40, 60, 100};

    int count = 5;

    srand(1);

    printf("========================================\n");
    printf("   TRAVELLING SALESPERSON PROBLEM\n");
    printf("========================================\n");

    printf("\nAlgorithm: Exact TSP using Backtracking\n");
    printf("Optimization: Branch and Bound\n");

    printf("\nRequired Problem Sizes:\n");
    printf("10, 20, 40, 60, 100\n");

    printf("\nNote:\n");
    printf("Exact TSP has factorial time complexity.\n");
    printf("Therefore very large instances are not\n");
    printf("executed to avoid impractical runtimes.\n");

    measureTime(sizes, count);

    printf("\nTheoretical growth:\n");
    printf("(n - 1)! possible tours\n");

    printf("\n========================================\n");

    return 0;
}