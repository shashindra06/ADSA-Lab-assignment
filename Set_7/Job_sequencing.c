#include <stdio.h>

struct Job {
    char id;
    int deadline;
    int profit;
};

int main() {
    struct Job jobs[] = {
        {'J1', 2, 100},
        {'J2', 1, 19},
        {'J3', 2, 27},
        {'J4', 1, 25},
        {'J5', 3, 15}
    };

    int n = 5;

    // Sort jobs by decreasing profit
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    // Find maximum deadline
    int maxDeadline = 0;

    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    char slot[maxDeadline + 1];
    int slotProfit[maxDeadline + 1];

    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = '-';
        slotProfit[i] = 0;
    }

    int totalProfit = 0;

    // Schedule jobs
    for (int i = 0; i < n; i++) {

        // Try the latest possible slot
        for (int j = jobs[i].deadline; j >= 1; j--) {

            if (slot[j] == '-') {
                slot[j] = jobs[i].id;
                slotProfit[j] = jobs[i].profit;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\n========================================\n");
    printf("     JOB SEQUENCING WITH DEADLINES\n");
    printf("========================================\n");

    printf("\nScheduled Jobs:\n");

    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            printf("Time Slot %d -> Job %c (Profit = %d)\n",
                   i, slot[i], slotProfit[i]);
        else
            printf("Time Slot %d -> No Job\n", i);
    }

    printf("\nMaximum Total Profit = %d\n", totalProfit);

    printf("========================================\n");

    return 0;
}