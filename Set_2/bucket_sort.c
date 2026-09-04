#include <stdio.h>

void insertionSort(int arr[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int temp = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = temp;
    }
}

void bucketSort(int arr[], int n)
{
    int buckets[10][100] = {0};
    int count[10] = {0};

    // Put elements into buckets
    for(int i = 0; i < n; i++)
    {
        int index = arr[i] / 10;

        if(index > 9)
            index = 9;

        buckets[index][count[index]++] = arr[i];
    }

    // Sort each bucket
    for(int i = 0; i < 10; i++)
        insertionSort(buckets[i], count[i]);

    // Combine buckets
    int k = 0;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < count[i]; j++)
            arr[k++] = buckets[i][j];
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
    int arr[] = {42, 15, 73, 26, 91, 38, 54, 67};
    int n = 8;

    printf("Before sort: ");
    display(arr, n);

    bucketSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}