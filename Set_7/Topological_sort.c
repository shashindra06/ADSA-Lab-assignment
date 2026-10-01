#include <stdio.h>

#define V 6

int graph[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};

void topologicalSort() {

    int indegree[V] = {0};
    int queue[V];

    int front = 0;
    int rear = 0;
    int count = 0;

    // Calculate indegree of every vertex
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {

            if (graph[i][j])
                indegree[j]++;
        }
    }

    // Add vertices having indegree 0
    for (int i = 0; i < V; i++) {

        if (indegree[i] == 0)
            queue[rear++] = i;
    }

    printf("\nTopological Order:\n");

    while (front < rear) {

        int current = queue[front++];

        printf("%d", current);

        count++;

        if (count < V)
            printf(" -> ");

        // Remove current vertex's outgoing edges
        for (int i = 0; i < V; i++) {

            if (graph[current][i]) {

                indegree[i]--;

                if (indegree[i] == 0)
                    queue[rear++] = i;
            }
        }
    }

    printf("\n");

    if (count == V) {
        printf("\nResult: Topological sorting completed successfully.\n");
        printf("The order respects all directed dependencies.\n");
    }
    else {
        printf("\nResult: Topological sorting is not possible.\n");
        printf("Reason: The graph contains a cycle.\n");
    }
}

int main() {

    printf("========================================\n");
    printf("          TOPOLOGICAL SORT\n");
    printf("========================================\n");

    printf("\nDirected Graph Dependencies:\n");
    printf("0 -> 1\n");
    printf("0 -> 2\n");
    printf("1 -> 3\n");
    printf("2 -> 3\n");
    printf("2 -> 4\n");
    printf("3 -> 5\n");
    printf("4 -> 5\n");

    topologicalSort();

    printf("========================================\n");

    return 0;
}