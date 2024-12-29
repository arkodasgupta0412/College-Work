#include <stdio.h>
#include <stdlib.h>
#include "maxHeap.c"
#include "minHeap.c"
#include "utils.c"

void bubbleSort(int arr[], int size, long long *cmp)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            (*cmp)++;
            if (arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

void insertionSort(int arr[], int size, long long *cmp)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i], j = i - 1;
        while (j >= 0)
        {
            (*cmp)++;
            if (arr[j] <= key)
                break;

            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size, long long *cmp)
{
    for (int i = 0; i < size; i++)
    {
        int mn = arr[i], mnIdx = i;
        for (int j = i + 1; j < size; j++)
        {
            (*cmp)++;
            if (arr[j] < mn)
            {
                mn = arr[j];
                mnIdx = j;
            }
        }
        int t = arr[i];
        arr[i] = mn;
        arr[mnIdx] = t;
    }
}

void merge(int arr[], int low, int mid, int high, long long *cmp)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int leftArr[n1], rightArr[n2];
    for (int i = 0; i < n1; i++)
    {
        leftArr[i] = arr[low + i];
    }
    for (j = 0; j < n2; j++)
    {
        rightArr[j] = arr[mid + 1 + j];
    }

    i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        (*cmp)++;
        if (leftArr[i] <= rightArr[j])
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = leftArr[i++];
    }

    while (j < n2)
    {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(int arr[], int low, int high, long long *cmp)
{
    if (low < high)
    {
        int mid = (low + high) >> 1;
        mergeSort(arr, low, mid, cmp);
        mergeSort(arr, mid + 1, high, cmp);
        merge(arr, low, mid, high, cmp);
    }
}

void heapSort(int arr[], int n, long long *cmp)
{
    build_max_heap(arr, n, cmp);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, i, 0, cmp);
    }
}

int partition(int arr[], int low, int high, long long *pCtr)
{

    int pivot = arr[high];

    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        (*pCtr)++;

        if (arr[j] < pivot)
        {
            (*pCtr)++;
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, long long *pCtr)
{
    if (low < high)
    {
        (*pCtr)++;

        int mid = partition(arr, low, high, pCtr);

        quickSort(arr, low, mid - 1, pCtr);
        quickSort(arr, mid + 1, high, pCtr);
    }
}