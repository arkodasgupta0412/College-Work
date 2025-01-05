/*
7. Take a four-digit prime number P. Generate a series of large integers L and for each member Li
compute the remainder Ri after dividing Li by P. Tabulate Li and Ri. Repeat for seven other four digit
prime numbers keeping Li fixed.
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>


void sieve(int *isPrime, int n) {
    for (int i = 0; i <= n; i++) {
        isPrime[i] = 1;
    }

    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; i*i <= n; i++) {
        if (isPrime[i] == 0) {
            continue;
        }

        for (int j = i*i; j <= n; j += i) {
            isPrime[j] = 0;
        }
    }
}


int main() {
    srand(time(NULL));
    int *isPrime = (int *) malloc(10000 * sizeof(int));
    sieve(isPrime, 9999);

    int ctr = 0;
    for (int i = 1000; i <= 9999 && ctr < 8; i++) {
        if (isPrime[i]) {
            for (int j = 0; j < 10; j++) {
                printf("%d %d %d\n", i, rand(), rand() % i);
            }
            printf("\n");

            ctr++;
        }
    }

    return 0;
}