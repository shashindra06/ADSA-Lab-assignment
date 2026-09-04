#include <stdio.h>

void countingSort(int arr[], int n)
{
    int max = arr[0];

    // Find maximum element
    for(int i = 1; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }

    int count[100] = {0};

    // Count frequency of each element
    for(int i = 0; i < n; i++)
        count[arr[i]]++;

    // Put elements back in sorted order
    int k = 0;

    for(int i = 0; i <= max; i++)
    {
        while(count[i] > 0)
        {
            arr[k++] = i;
            count[i]--;
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
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = 7;

    printf("Before sort: ");
    display(arr, n);

    countingSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}