/*
4. Write a program to generate 1,00,000 random integers between 1 and 1,00,000 without repetitions
and store them in a file in character mode one number per line. Study and use the functions in C
related to random numbers
*/


#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void swap(long long a[], long long i, long long j) {
    long long tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}


int main() {
    const long long N = 100;
    long long arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    srand(time(NULL));
    long long random;

    for (long long i = N - 1; i >= 0; i--) {
        random = ((long long)rand() * RAND_MAX + rand()) % ((long long)(i) + 1);

        if (i == random) {
            continue;
        }

        swap(arr, i, random);
    }

    FILE* fp = fopen("output.txt", "w");
    for (int i = 0; i < N; i++) {
        fprintf(fp, "%lld\n", arr[i]);
    }
    fclose(fp);

    return 0;
}


