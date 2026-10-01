#include <stdio.h>

int main() {
    int coins[] = {100, 50, 20, 10, 5, 2, 1};
    int n = 7;

    int amount;
    int originalAmount;
    int count = 0;

    printf("========================================\n");
    printf("       COIN CHANGE - GREEDY METHOD\n");
    printf("========================================\n");

    printf("Available denominations: ");
    for (int i = 0; i < n; i++) {
        printf("%d", coins[i]);

        if (i != n - 1)
            printf(", ");
    }

    printf("\n\nEnter the amount: ");
    scanf("%d", &amount);

    if (amount < 0) {
        printf("\nInvalid amount. Amount must be non-negative.\n");
        return 0;
    }

    originalAmount = amount;

    printf("\nGreedy selection process:\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {

        while (amount >= coins[i]) {

            printf("Remaining amount = %d -> Select coin %d\n",
                   amount, coins[i]);

            amount -= coins[i];
            count++;
        }
    }

    printf("----------------------------------------\n");

    if (amount == 0) {
        printf("\nCoin change completed successfully.\n");
        printf("Original amount      : %d\n", originalAmount);
        printf("Total number of coins: %d\n", count);
        printf("Amount remaining     : %d\n", amount);
    }
    else {
        printf("\nExact coin change is not possible.\n");
    }

    printf("========================================\n");

    return 0;
}