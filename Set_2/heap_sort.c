#include <stdio.h>

void swap(int i, int j, int arr[])
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest])
        largest = left;

    if(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest != i)
    {
        swap(i, largest, arr);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    // Build max heap
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one
    for(int i = n - 1; i > 0; i--)
    {
        swap(0, i, arr);
        heapify(arr, i, 0);
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
    int arr[] = {5, 3, 8, 4, 1, 2};
    int n = 6;

    printf("Before sort: ");
    display(arr, n);

    heapSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}