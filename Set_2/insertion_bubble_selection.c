#include <stdio.h>

void swap(int i, int j, int arr[])
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


// ---------------- INSERTION SORT ----------------

void insertionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j > 0; j--)
        {
            if(arr[j] < arr[j - 1])
            {
                swap(j, j - 1, arr);
            }
            else
            {
                break;
            }
        }
    }
}


// ---------------- BUBBLE SORT ----------------

void bubbleSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(j, j + 1, arr);
                swapped = 1;
            }
        }

        if(swapped == 0)
        {
            break;
        }
    }
}


// ---------------- SELECTION SORT ----------------

int maxi(int arr[], int i, int j)
{
    int max = i;

    for(int k = i + 1; k < j; k++)
    {
        if(arr[k] > arr[max])
        {
            max = k;
        }
    }

    return max;
}


void selectionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int max = maxi(arr, 0, n - i);

        int last = n - i - 1;

        swap(last, max, arr);
    }
}


// ---------------- DISPLAY ----------------

void display(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}


// ---------------- MAIN ----------------

int main()
{
    int arr[] = {5, 2, 6, 3, 1};
    int n = 5;

    printf("Before sort: ");
    display(arr, n);

    bubbleSort(arr, n);

    printf("After sort: ");
    display(arr, n);

    return 0;
}