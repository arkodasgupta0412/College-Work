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
    int arr[] = {1, 3, 2, 5, 4, 7, 6};
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
