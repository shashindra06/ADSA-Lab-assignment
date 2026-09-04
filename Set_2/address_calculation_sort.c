#include <stdio.h>

#define SIZE 10

void addressCalculationSort(int arr[], int n)
{
    int min = arr[0];
    int max = arr[0];

    // Find minimum and maximum
    for(int i = 1; i < n; i++)
    {
        if(arr[i] < min)
            min = arr[i];

        if(arr[i] > max)
            max = arr[i];
    }

    int bucket[SIZE][100] = {0};
    int count[SIZE] = {0};

    // Calculate address and place elements into buckets
    for(int i = 0; i < n; i++)
    {
        int address = (arr[i] - min) * SIZE / (max - min + 1);

        bucket[address][count[address]] = arr[i];
        count[address]++;
    }

    // Sort each bucket
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < count[i] - 1; j++)
        {
            for(int k = j + 1; k < count[i]; k++)
            {
                if(bucket[i][j] > bucket[i][k])
                {
                    int temp = bucket[i][j];
                    bucket[i][j] = bucket[i][k];
                    bucket[i][k] = temp;
                }
            }
        }
    }

    // Combine buckets
    int k = 0;

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < count[i]; j++)
        {
            arr[k++] = bucket[i][j];
        }
    }
}

void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int arr[] = {23, 15, 42, 31, 18, 54, 27, 36};
    int n = 8;

    printf("Before sort: ");
    display(arr, n);

    addressCalculationSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}