#include <stdio.h>

void swap(int i, int j, int arr[])
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void radixExchangeSort(int arr[], int left, int right, int bit)
{
    if(left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    while(i <= j)
    {
        while(i <= right && ((arr[i] >> bit) & 1) == 0)
            i++;

        while(j >= left && ((arr[j] >> bit) & 1) == 1)
            j--;

        if(i < j)
        {
            swap(i, j, arr);
            i++;
            j--;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

int getMaxBit(int arr[], int n)
{
    int max = arr[0];

    for(int i = 1; i < n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }

    int bit = 0;

    while(max > 1)
    {
        max /= 2;
        bit++;
    }

    return bit;
}

void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int arr[] = {10, 7, 5, 12, 3, 8};
    int n = 6;

    printf("Before sort: ");
    display(arr, n);

    int bit = getMaxBit(arr, n);

    radixExchangeSort(arr, 0, n - 1, bit);

    printf("After sort: ");
    display(arr, n);

    return 0;
}