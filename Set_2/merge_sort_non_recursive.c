#include <stdio.h>

#define MAX 100

struct Task
{
    int low;
    int high;
    int state;
};

void merge(int arr[], int low, int mid, int high)
{
    int temp[MAX];

    int i = low;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= high)
    {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i <= mid)
        temp[k++] = arr[i++];

    while(j <= high)
        temp[k++] = arr[j++];

    for(i = low, k = 0; i <= high; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(int arr[], int n)
{
    struct Task stack[MAX];
    int top = -1;

    // Push the complete array as the first task
    stack[++top].low = 0;
    stack[top].high = n - 1;
    stack[top].state = 0;

    while(top != -1)
    {
        struct Task current = stack[top--];

        int low = current.low;
        int high = current.high;

        // Nothing to divide if only one element
        if(low >= high)
            continue;

        int mid = (low + high) / 2;

        if(current.state == 0)
        {
            /*
                We need to:
                1. Divide left
                2. Divide right
                3. Merge

                Since stack is LIFO, push them in reverse order.
            */

            // Merge task
            stack[++top].low = low;
            stack[top].high = high;
            stack[top].state = 1;

            // Right half
            stack[++top].low = mid + 1;
            stack[top].high = high;
            stack[top].state = 0;

            // Left half
            stack[++top].low = low;
            stack[top].high = mid;
            stack[top].state = 0;
        }
        else
        {
            // Both halves are sorted, so merge them
            merge(arr, low, mid, high);
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