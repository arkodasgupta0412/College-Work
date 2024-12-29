#include <stdio.h>
#include "utils.h"

/* this file creates a max Heap from an unordered array,
further can be used for implementing Heap (descending order)*/

void min_heapify(int arr[], int n, int i, long long *cmp)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    (*cmp)++;
    if (l < n && arr[l] < arr[smallest])
        smallest = l;

    (*cmp)++;
    if (r < n && arr[r] < arr[smallest])
        smallest = r;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        min_heapify(arr, n, smallest, cmp);
    }
}

void build_min_heap(int arr[], int n, long long *cmp)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        min_heapify(arr, n, i, cmp);
    }
}

/*int main()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    build_min_heap(arr, size, &count);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}*/