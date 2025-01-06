/*
2.7. Write a C program to move the negative elements in an array to the front of array.
Example:
Input : 2 -7 10 12 5 -2 32 -4
Output: -7 -2 -4 2 10 12 5 32
*/


#include <stdio.h>
#include "utils.c"

void segregate(int num[], int res[], int size)
{
    int i;
    int j;
    j = 0;
    for (i = 0; i < size; i++)
    {
        if (num[i] < 0)
        {
            res[j] = num[i];
            j++;
        }
    }

    for (i = 0; i < size; i++)
    {
        if (num[i] >= 0)
        {
            res[j] = num[i];
            j++;
        }
    }
}

/*int main()
{
    int arr[] = {2, -7, 10, 12, 5, -2, 32, -4};
    int size = sizeof(arr) / sizeof(arr[0]);
    int res[size];

    printf("\nInput Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    segregate(arr, res, size);

    printf("\n\nOutput Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n\n");

    int arr1[] = {1, -1, 1, -1, 1, 1, -1, 1, -1, -1, 1};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    res[size1];

    printf("\nInput Array: ");
    for (int i = 0; i < size1; i++)
    {
        printf("%d ", arr1[i]);
    }

    segregate(arr1, res, size1);

    printf("\n\nOutput Array: ");
    for (int i = 0; i < size1; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n\n");
}*/