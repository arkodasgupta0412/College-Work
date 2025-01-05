/*
10. The Edit Distance between two strings is defined as the number of inserts and deletes of characters
needed to turn one into another. Write a program to find the Edit Distance between two strings of
capital letters.
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>


int main() {
    int n, m;

    printf("Enter size of first string: ");
    scanf("%d", &n);
    char *a = (char *) malloc((n + 1)*sizeof(char));
    printf("Enter first string: ");
    scanf("%s", a);

    printf("Enter size of second string: ");
    scanf("%d", &m);
    char *b = (char *) malloc((m + 1)*sizeof(char));
    printf("Enter first string: ");
    scanf("%s", b);

    printf("%s %s\n", a, b);


    int *prev = (int *) malloc(m * sizeof(int));
    int *cur = (int *) malloc(m * sizeof(int));

    bool found = false;
    for (int j = 0; j < m; j++) {
        if (a[0] == b[j]) {
            found = true;
        }

        if (!found) {
            prev[j] = j + 2;
        } else {
            prev[j] = j;
        }
    }


    found = false;
    if (a[0] == b[0]) {
        found = true;
    }

    for (int i = 1; i < n; i++) {
        if (a[i] == b[0]) {
            found = true;
        }

        if (!found) {
            cur[0] = i + 2;
        } else {
            cur[0] = i;
        }

        for (int j = 1; j < m; j++) {
            int val = INT_MAX;
            val = (val > prev[j] + 1) ? prev[j] + 1 : val;
            val = (val > cur[j - 1] + 1) ? cur[j - 1] + 1 : val;

            if (a[i] == b[j]) {
                val = (val > prev[j - 1]) ? prev[j - 1] : val;
            }

            cur[j] = val;
        }

        for (int j = 0; j < m; j++) {
            prev[j] = cur[j];
        }
    }

    printf("The edit distance of the given strings is: %d\n", cur[m - 1]);

    return 0;
}