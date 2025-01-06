/*
2.5. Given a large single dimensional array of integers, write functions for sliding window filter with
maximum, minimum, median, and average to generate an output array. The window size should be an odd
integer like 3, 5 or 7. Explain what you will do with the boundary values. (Use zero-padding in both ends
of the arrays as necessary.)
Input Output examples for problem no. 2.5
Input: 4, 5, 1, 13, 3, 25, 27, 18, 10, 3, 4, 9
Window size: 3
Max filter output: 5, 5, 13, 13, 25, 27, 27, 27, 18, 10, 9, 9
Min filter output: 0, 1, 1, 1, 3, 3, 18, 10, 3, 3, 3, 0
Median filter output: 4, 4, 5, 3, 13, 25, 25, 18, 10, 4, 4, 4
2.6. Find whether an array is sorted or not, and the sorting order.
2.7. Write a C program to move the negative elements in an array to the front of array.
Example:
Input : 2 -7 10 12 5 -2 32 -4
Output: -7 -2 -4 2 10 12 5 32
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void zeroPadArray(int *arr, int *paddedArr, int size, int windowSize)
{
    int padding = (windowSize - 1) / 2;
    for (int i = 0; i < padding; i++)
    {
        paddedArr[i] = 0;
    }
    for (int i = 0; i < size; i++)
    {
        paddedArr[i + padding] = arr[i];
    }
    for (int i = size + padding; i < size + 2 * padding; i++)
    {
        paddedArr[i] = 0;
    }
}

int findMax(int *window, int windowSize)
{
    int max = window[0];
    for (int i = 1; i < windowSize; i++)
    {
        if (window[i] > max)
        {
            max = window[i];
        }
    }
    return max;
}

int findMin(int *window, int windowSize)
{
    int min = window[0];
    for (int i = 1; i < windowSize; i++)
    {
        if (window[i] < min)
        {
            min = window[i];
        }
    }
    return min;
}

int compareInts(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int findMedian(int *window, int windowSize)
{
    qsort(window, windowSize, sizeof(int), compareInts);
    return window[windowSize / 2];
}

double findAverage(int *window, int windowSize)
{
    double sum = 0;
    for (int i = 0; i < windowSize; i++)
    {
        sum += window[i];
    }
    return sum / windowSize;
}

void slidingWindowFilter(int *arr, int *output, int size, int windowSize, char operation)
{
    int padding = (windowSize - 1) / 2;
    int *paddedArr = (int *)malloc(sizeof(int) * (size + 2 * padding));

    zeroPadArray(arr, paddedArr, size, windowSize);

    for (int i = 0; i < size; i++)
    {
        int *window = (int *)malloc(sizeof(int) * windowSize);

        for (int j = 0; j < windowSize; j++)
        {
            window[j] = paddedArr[i + j];
        }

        switch (operation)
        {
        case 'M': // Max
            output[i] = findMax(window, windowSize);
            break;
        case 'm': // Min
            output[i] = findMin(window, windowSize);
            break;
        case 'A': // Average
            output[i] = (int)round(findAverage(window, windowSize));
            break;
        case 'a': // Median
            output[i] = findMedian(window, windowSize);
            break;
        default:
            printf("Unknown operation!\n");
            free(window);
            continue;
        }

        free(window);
    }

    free(paddedArr);
}

int main()
{
    int arr[] = {4, 5, 1, 13, 3, 25, 27, 18, 10, 3, 4, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int windowSize = 3;
    int *output = (int *)malloc(sizeof(int) * size);

    printf("Original array:\n");
    printArray(arr, size);

    printf("\nSliding window with maximum filter:\n");
    slidingWindowFilter(arr, output, size, windowSize, 'M');
    printArray(output, size);

    printf("\nSliding window with minimum filter:\n");
    slidingWindowFilter(arr, output, size, windowSize, 'm');
    printArray(output, size);

    printf("\nSliding window with average filter:\n");
    slidingWindowFilter(arr, output, size, windowSize, 'A');
    printArray(output, size);

    printf("\nSliding window with median filter:\n");
    slidingWindowFilter(arr, output, size, windowSize, 'a');
    printArray(output, size);

    free(output);
    return 0;
}
