/* 
2. Write a program to generate the nth Fibonacci number iteratively and recursively. Check when there
is overflow in the result and change the data types for accommodating higher values of inputs. Plot
the Fibonacci number vs n graph.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>


void fibIterative(int n) {
    char message[100] = "The required number is(iteratively): ";
    if (n == 1 || n == 2) {
        printf("%s 1\n", message);
        return;
    }

    int intPrev = 1;
    int intPrevPrev = 1;
    int intVal;

    long long longPrev, longPrevPrev, longVal;

    bool useLong = false;

    for (int i = 3; i <= n; i++) {
        if (useLong) {
            if (LONG_MAX - longPrev >= longPrevPrev) {
                longVal = longPrev + longPrevPrev;
                longPrevPrev = longPrev;
                longPrev = longVal;
            } else {
                printf("Long long Overflow at fibonacci number %d. Aborting!\n", i);

                exit(1);
            }
        } else {
            if (INT_MAX - intPrev >= intPrevPrev) {
                intVal = intPrev + intPrevPrev;
                intPrevPrev = intPrev;
                intPrev = intVal;
            } else {
                printf("Integer Overflow at fibonacci number %d.\n", i);

                useLong = true;
                longVal = (long long) intPrev + (long long) intPrevPrev;
                longPrev = longVal;
                longPrevPrev = intPrev;
            }
        }
    }

    if (useLong) {
        printf("%s %lld\n", message, longVal);
    } else {
        printf("%s %d\n", message, intVal);
    }
}


long long fibRecursive(int n, bool useLong) {
    
}


void main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    for (int i = 5; i <= 50; i += 5) {
        fibIterative(i);
    }
}