#include <stdio.h>

#define MAX 100

void merge(int arr[], int left, int mid, int right)
{
    int temp[MAX];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right)
    {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= mid)
        temp[k++] = arr[i++];

    while(j <= right)
        temp[k++] = arr[j++];

    for(i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(int arr[], int n)
{
    // size represents the size of each sorted group
    for(int size = 1; size < n; size *= 2)
    {
        // left represents the beginning of each pair of groups
        for(int left = 0; left < n - 1; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = left + 2 * size - 1;

            // Handle the last incomplete group
            if(mid >= n - 1)
                continue;

            if(right >= n)
                right = n - 1;

            merge(arr, left, mid, right);
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
    int arr[] = {8, 3, 5, 4, 7, 6, 1, 2};
    int n = 8;

    printf("Before sort: ");
    display(arr, n);

    mergeSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}