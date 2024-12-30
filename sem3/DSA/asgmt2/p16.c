#include <stdio.h>
#include <time.h>
#include "generate.c"
#include "sorting.c"

void bubble_sort(int arr[], int size, long long *cmp)
{
    bubbleSort(arr, size, cmp);
}

void insertion_sort(int arr[], int size, long long *cmp)
{
    insertionSort(arr, size, cmp);
}

void selection_sort(int arr[], int size, long long *cmp)
{
    selectionSort(arr, size, cmp);
}

void merge_sort(int arr[], int size, long long *cmp)
{
    mergeSort(arr, 0, size - 1, cmp);
}

void heap_sort(int arr[], int size, long long *cmp)
{
    heapSort(arr, size, cmp);
}

void quick_sort(int arr[], int size, long long *cmp)
{
    quickSort(arr, 0, size - 1, cmp);
}

int main()
{
    int size = 100000;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    generate(arr, size);
    clock_t t_start, t_end;
    double time_bubble, time_insertion, time_selection, time_merge, time_heap, time_quick;

    // Bubble Sort

    /*t_start = clock();
    long long cmpbs = 0;
    bubble_sort(arr, size, &cmpbs);
    t_end = clock();
    time_bubble = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort Comparisons: %lld\n", cmpbs);
    printf("Bubble Sort Time: %.4f seconds\n\n", time_bubble);*/

    // Insertion Sort

    /*t_start = clock();
    long long cmpis = 0;
    insertion_sort(arr, size, &cmpis);
    t_end = clock();
    time_insertion = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Insertion Sort Comparisons: %lld\n", cmpis);
    printf("Insertion Sort Time: %.4f seconds\n\n", time_insertion);*/

    // Selection Sort

    /*t_start = clock();
    long long cmpss = 0;
    selection_sort(arr, size, &cmpss);
    t_end = clock();
    time_selection = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Selection Sort Comparisons: %lld\n", cmpss);
    printf("Selection Sort Time: %.4f seconds\n\n", time_selection);*/

    // Merge Sort

    long long cmpms = 0;
    t_start = clock();
    merge_sort(arr, size, &cmpms);
    t_end = clock();
    time_merge = ((long double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Merge Sort Comparisons: %lld\n", cmpms);
    printf("Merge Sort Time: %.4f seconds\n\n", time_merge);

    // Heap Sort

    /*long long cmphs = 0;
    t_start = clock();
    heap_sort(arr, size, &cmphs);
    t_end = clock();
    time_heap = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Heap Sort Comparisons: %lld\n", cmphs);
    printf("Heap Sort Time: %.4f seconds\n\n", time_heap);*/

    // Quick Sort

    /*long long cmpqs = 0;
    t_start = clock();
    quick_sort(arr, size, &cmpqs);
    t_end = clock();
    time_quick = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("Quick Sort Comparisons: %lld\n", cmpqs);
    printf("Quick Sort Time: %.4f seconds\n\n", time_quick);*/

    free(arr);
    return 0;
}
