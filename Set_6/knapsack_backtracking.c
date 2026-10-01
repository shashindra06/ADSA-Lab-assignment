#include <stdio.h>

#define N 4
#define CAPACITY 7

int weight[N] = {1, 3, 4, 5};
int value[N] = {1, 4, 5, 7};

int currentSelection[N];
int bestSelection[N];

int bestValue = 0;
int bestWeight = 0;

void knapsack(int index, int currentWeight, int currentValue)
{
    if (index == N)
    {
        if (currentValue > bestValue)
        {
            bestValue = currentValue;
            bestWeight = currentWeight;

            for (int i = 0; i < N; i++)
                bestSelection[i] = currentSelection[i];
        }

        return;
    }

    /* Choice 1: Include item */
    if (currentWeight + weight[index] <= CAPACITY)
    {
        currentSelection[index] = 1;

        knapsack(index + 1,
                 currentWeight + weight[index],
                 currentValue + value[index]);

        currentSelection[index] = 0;
    }

    /* Choice 2: Exclude item */
    currentSelection[index] = 0;

    knapsack(index + 1,
             currentWeight,
             currentValue);
}

int main()
{
    printf("========== 0/1 KNAPSACK - BACKTRACKING ==========\n\n");

    printf("Capacity = %d\n\n", CAPACITY);

    for (int i = 0; i < N; i++)
    {
        printf("Item %d: Weight = %d, Value = %d\n",
               i + 1, weight[i], value[i]);
    }

    knapsack(0, 0, 0);

    printf("\nBest solution found using backtracking:\n");

    for (int i = 0; i < N; i++)
    {
        if (bestSelection[i])
        {
            printf("Item %d -> Weight = %d, Value = %d\n",
                   i + 1, weight[i], value[i]);
        }
    }

    printf("\nMaximum value = %d\n", bestValue);
    printf("Total weight = %d\n", bestWeight);

    return 0;
}