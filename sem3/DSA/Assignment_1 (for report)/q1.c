/*
1. Write a program to compute the factorial of an integer n iteratively and recursively. Check when
there is overflow in the result and change the data types for accommodating higher values of inputs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


void getIO(int *);
void factorialRecursive(int, int, bool, int, long long);
void factorialIterative(int);


int main() {
    int n;
    getIO(&n);

    factorialIterative(n);
    factorialRecursive(n, 1, false, 1, 1);
}


void factorialIterative(int n) {
    long long longFact;
    int intFact = 1;
    bool isLong = false;

    for (int i = 1; i <= n; i++) {
        if (isLong) {
            if ((LONG_MAX / longFact) < i) {
                printf("Factorial is too large to be represented. Aborting...\n");
                exit(0);
            } else {
                longFact *= i;
            }
        } else {
            if ((INT_MAX / intFact) >= i) {
                intFact *= i;
            } else {
                longFact = intFact;
                longFact *= i;
                isLong = true;
            }
        }
    }

    char text[100] = "The factorial using iterative method is:";

    if (isLong) {
        printf("%s %lld\n", text, longFact); 
    } else {
        printf("%s %d\n", text, intFact);
    }
}


void factorialRecursive(int n, int i, bool isLong, int intFact, long long longFact) {
    if (i == n + 1) {
        char text[100] = "The factorial using iterative method is:";

        if (isLong) {
            printf("%s %lld\n", text, longFact); 
        } else {
            printf("%s %d\n", text, intFact);
        }

        return;
    }


    if (isLong) {
        if ((LONG_MAX / longFact) < i) {
            printf("Factorial is too large to be represented. Aborting...\n");
            exit(0);
        } else {
            longFact *= i;
        }        
    } else {
        if ((INT_MAX / intFact) >= i) {
                intFact *= i;
            } else {
                longFact = intFact;
                longFact *= i;
                isLong = true;
            }
    }

    factorialRecursive(n, i + 1, isLong, intFact, longFact);
}


void getIO(int *n) {
    printf("Enter a number: ");
    scanf("%d", n);
}