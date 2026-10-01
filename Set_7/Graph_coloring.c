#include <stdio.h>

#define V 4
#define COLORS 3

int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}
};

int color[V] = {0};

int isSafe(int vertex, int selectedColor) {

    for (int i = 0; i < V; i++) {

        if (graph[vertex][i] &&
            color[i] == selectedColor) {
            return 0;
        }
    }

    return 1;
}

int graphColoring(int vertex) {

    // All vertices have been colored
    if (vertex == V)
        return 1;

    for (int c = 1; c <= COLORS; c++) {

        if (isSafe(vertex, c)) {

            color[vertex] = c;

            if (graphColoring(vertex + 1))
                return 1;

            // Backtrack
            color[vertex] = 0;
        }
    }

    return 0;
}

int main() {

    printf("\n========================================\n");
    printf("        GRAPH COLORING - BACKTRACKING\n");
    printf("========================================\n");

    printf("\nGraph has %d vertices and %d available colors.\n",
           V, COLORS);

    if (graphColoring(0)) {

        printf("\nValid coloring found:\n");

        for (int i = 0; i < V; i++) {
            printf("Vertex %d -> Color %d\n",
                   i, color[i]);
        }

        printf("\nResult: All adjacent vertices have different colors.\n");
    }
    else {
        printf("\nNo valid coloring exists using %d colors.\n",
               COLORS);
    }

    printf("========================================\n");

    return 0;
}