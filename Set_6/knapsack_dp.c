#include <stdio.h>

#define N 4
#define CAPACITY 7

int max(int a, int b)
{
    return a > b ? a : b;
}

void knapsack(int weight[], int value[])
{
    int dp[N + 1][CAPACITY + 1];

    for (int i = 0; i <= N; i++)
    {
        for (int w = 0; w <= CAPACITY; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w)
            {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("DP Table:\n\n");

    printf("     ");
    for (int w = 0; w <= CAPACITY; w++)
        printf("%3d ", w);

    printf("\n");

    for (int i = 0; i <= N; i++)
    {
        printf("i=%d: ", i);

        for (int w = 0; w <= CAPACITY; w++)
            printf("%3d ", dp[i][w]);

        printf("\n");
    }

    int w = CAPACITY;
    int selected[N];
    int count = 0;

    for (int i = N; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected[count++] = i - 1;
            w -= weight[i - 1];
        }
    }

    printf("\nMaximum profit = %d\n", dp[N][CAPACITY]);

    printf("Selected items:\n");

    for (int i = count - 1; i >= 0; i--)
    {
        int item = selected[i];

        printf("Item %d -> Weight = %d, Value = %d\n",
               item + 1,
               weight[item],
               value[item]);
    }

    printf("Total weight = %d\n", CAPACITY - w);
}

int main()
{
    int weight[N] = {1, 3, 4, 5};
    int value[N] = {1, 4, 5, 7};

    printf("========== 0/1 KNAPSACK - DYNAMIC PROGRAMMING ==========\n\n");

    printf("Capacity = %d\n\n", CAPACITY);

    for (int i = 0; i < N; i++)
    {
        printf("Item %d: Weight = %d, Value = %d\n",
               i + 1, weight[i], value[i]);
    }

    printf("\n");

    knapsack(weight, value);

    return 0;
}