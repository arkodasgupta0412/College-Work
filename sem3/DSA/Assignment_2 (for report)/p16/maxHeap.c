#include <stdio.h>
#include "../utils.h"

/* this file creates a max Heap from an unordered array,
further can be used for implementing Heap (ascending order)*/

void max_heapify(int arr[], int n, int i, long long *cmp)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;

    (*cmp)++;
    if (l < n && arr[l] > arr[largest])
        largest = l;

    (*cmp)++;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest, cmp);
    }
}

void build_max_heap(int arr[], int n, long long *cmp)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_heapify(arr, n, i, cmp);
    }
}

/*int main()
{
    int arr[] = {3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    int size = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    build_max_heap(arr, size, &count);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}*/