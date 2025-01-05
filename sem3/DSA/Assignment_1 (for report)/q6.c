/*
6. Store the names of your classmates according to roll numbers in a text file one name per line. Write
a program to find out from the file, the smallest and largest names and their lengths in number of
characters. Write a function to sort the names alphabetically and store in a second file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int getData() {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Couldn't open file for writing.\n");
        exit(1);
    }

    printf("Enter number of students: ");
    int n;
    scanf("%d", &n);

    char name[101];
    for (int i = 1; i <= n; i++) {
        printf("Enter name of student with roll number %d: ", i);
        scanf("%100s", name);

        fprintf(fp, "%d %s\n", i, name);
    }

    fclose(fp);
    return n;
}

void findExtrema(int n) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Couldn't open file.\n");
        return;
    }

    int roll;
    char name[101];

    char smallestName[101];
    char largestName[101];
    smallestName[0] = '\0';
    largestName[0] = '\0';

    int *lengths = (int *) malloc(n * sizeof(int));
    if (lengths == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d %s", &roll, name) != 2) {
            printf("Error reading data.\n");
            free(lengths);
            fclose(fp);
            return;
        }

        if (strlen(smallestName) == 0 || strcmp(smallestName, name) > 0) {
            strcpy(smallestName, name);
        }

        if (strlen(largestName) == 0 || strcmp(largestName, name) < 0) {
            strcpy(largestName, name);
        }

        lengths[i] = strlen(name);
    }

    fclose(fp);

    printf("Smallest name: %s\n", smallestName);
    printf("Length: %d\n", strlen(smallestName));
    printf("Largest name: %s\n", largestName);
    printf("Length: %d\n", strlen(largestName));
    printf("Lengths of names: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", lengths[i]);
    }
    printf("\n");

    free(lengths);
}

void sortAndStore(int n) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Couldn't open file for reading.\n");
        return;
    }

    char names[n][101];
    int rolls[n];

    int i = 0;
    while (fscanf(fp, "%d %s", &rolls[i], names[i]) == 2) {
        i++;
    }

    fclose(fp);

    for (int j = 0; j < n - 1; j++) {
        for (int k = j + 1; k < n; k++) {
            if (strcmp(names[j], names[k]) > 0) {
                char tempName[101];
                int tempRoll;

                strcpy(tempName, names[j]);
                tempRoll = rolls[j];

                strcpy(names[j], names[k]);
                rolls[j] = rolls[k];

                strcpy(names[k], tempName);
                rolls[k] = tempRoll;
            }
        }
    }

    FILE *outFp = fopen("sorted_students.txt", "w");
    if (outFp == NULL) {
        printf("Couldn't open file for writing.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(outFp, "%d %s\n", rolls[i], names[i]);
    }

    fclose(outFp);
}

int main() {
    int n = getData();
    findExtrema(n);
    sortAndStore(n);

    return 0;
}
