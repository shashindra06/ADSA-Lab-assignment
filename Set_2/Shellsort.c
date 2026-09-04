#include <stdio.h>

void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void shellSort(int arr[], int n)
{
    // Start with a large gap and keep reducing it
    for(int gap = n / 2; gap > 0; gap /= 2)
    {
        // Insertion sort with the given gap
        for(int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while(j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

int main()
{
    int arr[] = {9, 8, 3, 7, 5, 6, 4, 1};
    int n = 8;

    printf("Before sort: ");
    display(arr, n);

    shellSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}