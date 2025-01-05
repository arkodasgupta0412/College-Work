#include <stdio.h>

typedef enum
{
    UNSORTED,
    ASCENDING,
    DESCENDING
} SortOrder;

SortOrder checkSorted(int arr[], int n)
{
    if (n <= 1)
        return ASCENDING;

    int ascending = 1, descending = 1;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
            ascending = 0;
        if (arr[i] > arr[i - 1])
            descending = 0;
    }

    if (ascending)
        return ASCENDING;
    if (descending)
        return DESCENDING;
    return UNSORTED;
}

/*int main()
{
    // Example 1: Ascending order array
    int arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Array 1: ");
    for (int i = 0; i < size1; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\nResult: ");
    SortOrder order1 = checkSorted(arr1, size1);
    if (order1 == ASCENDING)
        printf("Sorted. Ascending order\n");
    else if (order1 == DESCENDING)
        printf("Sorted. Descending order\n");
    else
        printf("Unsorted\n");

    // Example 2: Descending order array
    int arr2[] = {10, 8, 6, 4, 2};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("\nArray 2: ");
    for (int i = 0; i < size2; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\nResult: ");
    SortOrder order2 = checkSorted(arr2, size2);
    if (order2 == ASCENDING)
        printf("Sorted. Ascending order\n");
    else if (order2 == DESCENDING)
        printf("Sorted. Descending order\n");
    else
        printf("Unsorted\n");

    // Example 3: Unsorted array
    int arr3[] = {1, 5, 2, 8, 4};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("\nArray 3: ");
    for (int i = 0; i < size3; i++)
    {
        printf("%d ", arr3[i]);
    }
    printf("\nResult: ");
    SortOrder order3 = checkSorted(arr3, size3);
    if (order3 == ASCENDING)
        printf("Sorted. Ascending order\n");
    else if (order3 == DESCENDING)
        printf("Sorted. Descending order\n");
    else
        printf("Unsorted\n");

    return 0;
}*/