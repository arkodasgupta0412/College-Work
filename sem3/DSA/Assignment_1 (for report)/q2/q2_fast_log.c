/* 
2. Write a program to generate the nth Fibonacci number iteratively and recursively. Check when there
is overflow in the result and change the data types for accommodating higher values of inputs. Plot
the Fibonacci number vs n graph.
*/

/*
Here a logarithmic approach is taken for fibonacci sequence using 
matrix exponentiation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>


#include <stdint.h>

#define BINPOW(TYPE)                                            \
void binpow_##TYPE(TYPE a[2][2], int exp) {                     \
    if (exp == 1) {                                             \
        return;                                                 \
    }                                                           \
                                                                \
    TYPE old_a[2][2];                                           \
    for (int i = 0; i < 2; i++) {                               \
        for (int j = 0; j < 2; j++) {                           \
            old_a[i][j] = a[i][j];                              \
        }                                                       \
    }                                                           \
                                                                \
    binpow_##TYPE(a, exp >> 1);                                 \
                                                                \
    TYPE b[2][2];                                               \
    for (int i = 0; i < 2; i++) {                               \
        for (int j = 0; j < 2; j++) {                           \
            b[i][j] = 0;                                        \
            for (int k = 0; k < 2; k++) {                       \
                b[i][j] += a[i][k] * a[k][j];                   \
            }                                                   \
        }                                                       \
    }                                                           \
                                                                \
    for (int i = 0; i < 2; i++) {                               \
        for (int j = 0; j < 2; j++) {                           \
            a[i][j] = b[i][j];                                  \
        }                                                       \
    }                                                           \
                                                                \
    if (exp % 2 == 1) {                                         \
        for (int i = 0; i < 2; i++) {                           \
            for (int j = 0; j < 2; j++) {                       \
                b[i][j] = 0;                                    \
                for (int k = 0; k < 2; k++) {                   \
                    b[i][j] += a[i][k] * old_a[k][j];           \
                }                                               \
            }                                                   \
        }                                                       \
                                                                \
        for (int i = 0; i < 2; i++) {                           \
            for (int j = 0; j < 2; j++) {                       \
                a[i][j] = b[i][j];                              \
            }                                                   \
        }                                                       \
    }                                                           \
}

#define FIB_RECURSIVE(TYPE)                                     \
void fibRecursive_##TYPE(int n) {                               \
    char text[100] = "The required number is (recursively): ";  \
    if (n == 1 || n == 2) {                                     \
        printf("%s 1\n", text);                                 \
        return;                                                 \
    }                                                           \
                                                                \
    if (n == 3) {                                               \
        printf("%s %d\n", text, 2);                             \
        return;                                                 \
    }                                                           \
                                                                \
    TYPE a[2][2] = {                                            \
        {0, 1},                                                 \
        {1, 1}                                                  \
    };                                                          \
                                                                \
    TYPE v[2] = {1, 1};  /* F_1, F_2 */                         \
                                                                \
    int exp = n - 2;                                            \
                                                                \
    binpow_##TYPE(a, exp);                                      \
                                                                \
    TYPE val = a[1][0] * v[0] + a[1][1] * v[1];                 \
    printf("%s %lld \n", text, (long long)val);                 \
}



void getIO(int *);
bool fibIterative(int);
void fibRecursiveInt(int);
void fibRecursiveLong(int);
void drawGraph();

BINPOW(int)
BINPOW(int64_t)
FIB_RECURSIVE(int)
FIB_RECURSIVE(int64_t)

int main() {
    int n;
    getIO(&n);

    bool isLong = fibIterative(n);
    
    if (isLong) {
        fibRecursive_int64_t(n);
    } else {
        fibRecursive_int(n);
    }

    drawGraph();
}


bool fibIterative(int n) {
    /*
    Implements the dp approach with space optimisations
    */

    char text[100] = "The required number is (iteratively): ";
    if (n < 1) {
        printf("Invalid input! Aborting...");
        exit(0);
        return false;
    }

    if (n == 1 || n == 2) {
        printf("%s %d\n", text, 1);
        return false;
    }

    int intPrev = 1, intPrev2 = 1, intCur;
    long long longPrev, longPrev2, longCur;

    bool isLong = false;

    for (int i = 3; i <= n; i++) {
        if (isLong) {
            if (LONG_MAX - longPrev < longPrev2) {
                printf("Too Large of a number! Aborting...\n");
                exit(0);
            } else {
                longCur = longPrev + longPrev2;
                longPrev2 = longPrev;
                longPrev = longCur;
            }
        } else {
            if (INT_MAX - intPrev < intPrev2) {
                isLong = true;

                longCur = (long long)intPrev + (long long)intPrev2;
                longPrev = longCur;
                longPrev2 = intPrev;
            } else {
                intCur = intPrev + intPrev2;
                intPrev2 = intPrev;
                intPrev = intCur;
            }
        }
    }


    if (isLong) {
        printf("%s %lld\n", text, longCur);
    } else {
        printf("%s %d\n", text, intCur);
    }

    return isLong;
}

/*
void binpow(int a[2][2], int exp) {
    if (exp == 1) {
        return;
    }

    int old_a[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            old_a[i][j] = a[i][j];
        }
    }

    binpow(a, exp >> 1);

    int b[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            b[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                b[i][j] = a[i][k] * a[k][j];
            }
        }
    }

    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a[i][j] = b[i][j];
        }
    }

    if (exp % 2 == 1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                b[i][j] = 0;
                for (int k = 0; k < 2; k++) {
                    b[i][j] = a[i][k] * old_a[k][j];
                }
            }
        }

        for(int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                a[i][j] = old_a[i][j];
            }
        }
    }
}



void fibRecursiveInt(int n) {

    if (n == 1 || n == 2) {
        printf("1\n");
    }

    if (n == 3) {
        printf("%d\n", 2);
    }

    int a[2][2] = {
        {0, 1},
        {1, 1}
    };

    int v[2] = {1, 1}; // F_1, F_2

    int exp = n - 2;

    binpow(a, exp);

    int val = a[1][0]*v[0] + a[1][1]*v[1];
    printf("%d\n", val);
}
*/


void fibRecursiveLong(int n) {

}


void drawGraph() {
    // upto 10

    int prev = 1, prev2 = 1, cur;

    printf(" 1|  %c\n", '*');
    printf(" 2|  %c\n", '*');

    for (int i = 3; i <= 10; i++) {
        cur = prev + prev2;
        prev2 = prev;
        prev = cur;

        printf("%2d|  ", i);
        for (int i = 0; i < cur; i++) {
            printf("%c", '*');
        }
        printf("\n");
    }
}


void getIO(int *n) {
    printf("Enter a number: ");
    scanf("%d", n);
}