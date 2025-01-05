/*
3. Write programs for linear search and binary search for searching integers, floating point numbers
and words in arrays of respective types.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define BINARY_SEARCH(TYPE, BS_FN, COMPARE)                                   \
int BS_FN(TYPE *a, int n, TYPE target) {                                      \
    int low = 0, high = n - 1, mid;                                           \
                                                                              \
    while (low <= high) {                                                     \
        mid = low + (high - low) / 2;                                         \
                                                                              \
        if (COMPARE(a[mid], target) == 0) {                                   \
            return mid;                                                       \
        } else if (COMPARE(a[mid], target) > 0) {                             \
            high = mid - 1;                                                   \
        } else {                                                              \
            low = mid + 1;                                                    \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}


#define LINEAR_SEARCH(TYPE, LS_FN, COMPARE)                                   \
int LS_FN(TYPE *a, int n, TYPE target) {                                      \
    for (int i = 0; i < n; i++) {                                             \
        if (COMPARE(a[i], target) == 0) {                                     \
            return i;                                                         \
        }                                                                     \
    }                                                                         \
                                                                              \
    return -1;                                                                \
}


#define GET_IO(TYPE, SPECIFIER, FN)                                            \
void FN(int *n, TYPE **a, TYPE *target) {                                      \
    printf("Enter number of sorted elements: ");                               \
    scanf("%d", n);                                                            \
    printf("Enter target: ");                                                  \
    scanf(SPECIFIER, target);                                                  \
                                                                               \
    (*a) = (TYPE *) malloc((*n) * sizeof(TYPE));                               \
    if (*a == NULL) {                                                          \
        printf("Memory allocation failed.\n");                                 \
        exit(1);                                                               \
    }                                                                          \
                                                                               \
    for (int i = 0; i < *n; i++) {                                             \
        printf("Enter element %d: ", i + 1);                                   \
        scanf(SPECIFIER, &(*a)[i]);                                            \
    }                                                                          \
}


int cmpInt(int, int);
float cmpFloat(float, float);
int cmpWords(char *, char *);
void getIO_Words(int *, char ***, char **);

GET_IO(int, "%d", getIO_int)
GET_IO(float, "%f", getIO_float);

BINARY_SEARCH(int, binarySearchInt, cmpInt);
BINARY_SEARCH(float, binarySearchFloat, cmpFloat);
BINARY_SEARCH(char*, binarySearchWords, cmpWords);
LINEAR_SEARCH(int, LinearSearchInt, cmpInt);
LINEAR_SEARCH(float, LinearSearchFloat, cmpFloat);
LINEAR_SEARCH(char*, LinearSearchWords, cmpWords);


int main() {
    printf("Enter 1 for int, 2 for float, 3 for words: ");
    int response;
    scanf("%d", &response);

    int n;
    int ansBS, ansLS;
    int targetInt;
    int *aInt;
    float targetFloat;
    float *aFloat;
    char *targetWords = (char *) malloc(101 * sizeof(char));
    char **aWords;
    switch (response) {
        case 1:
            getIO_int(&n, &aInt, &targetInt);

            ansBS = binarySearchInt(aInt, n, targetInt);
            ansLS = LinearSearchInt(aInt, n, targetInt);

            free(aInt);
            break;

        case 2:
            getIO_float(&n, &aFloat, &targetFloat);

            ansBS = binarySearchFloat(aFloat, n, targetFloat);
            ansLS = LinearSearchFloat(aFloat, n, targetFloat);
            free(aFloat);
            break;

        case 3:
            getIO_Words(&n, &aWords, &targetWords);

            ansBS = binarySearchWords(aWords, n, targetWords);
            ansLS = LinearSearchWords(aWords, n, targetWords);

            free(targetWords);
            for (int i = 0; i < n; i++) {
                free(aWords[i]);
            }
            free(aWords);
            break;
    }

    printf("Using Binary Search: \n");
    if (ansBS == -1) {
        printf("Answer not found!\n");
    } else {
        printf("Answer = %d\n", ansBS);
    }

    printf("Using Linear Search: \n");
    if (ansLS == -1) {
        printf("Answer not found!\n");
    } else {
        printf("Answer = %d\n", ansLS);
    }

    return 0;
}


void getIO_Words(int *n, char ***a, char **target) {
    printf("Enter number of sorted elements: ");
    scanf("%d", n); 
    printf("Enter target: ");
    scanf("%99s", *target);
                                                                             
    (*a) = (char **) malloc((*n) * sizeof(char *));                             
    if (*a == NULL) {                                                      
        printf("Memory allocation failed.\n");                               
        exit(1);                                                           
    }

    for (int i = 0; i < *n; i++) {
        (*a)[i] = (char *) malloc(101 * sizeof(char));
    } 
                                                                            
    for (int i = 0; i < *n; i++) {                                          
        printf("Enter element %d: ", i + 1);                                
        scanf("%99s", (*a)[i]);                                  
    }
}


int cmpInt(int a, int b) {
    return a - b;
}


float cmpFloat(float a, float b) {
    if (((a - b > 0) ? (a - b) : (b - a)) < 0.00001) {
        return 0;
    }
    
    return a - b;
}


int cmpWords(char *a, char *b) {
    return strcmp(a, b);
}
