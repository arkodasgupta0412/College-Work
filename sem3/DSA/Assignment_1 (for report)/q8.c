/*
8. Convert your Name and Surname into large integers by juxtaposing integer ASCII codes for alphabet.
Print the corresponding converted integer. Cut the large integers into two halves and add the two
halves. Compute the remainder after dividing the result by the prime numbers P in problem 7.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sieve(int *isPrime, int n) {
    for (int i = 0; i <= n; i++) {
        isPrime[i] = 1;
    }

    isPrime[0] = isPrime[1] = 0;

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i] == 0) {
            continue;
        }

        for (int j = i * i; j <= n; j += i) {
            isPrime[j] = 0;
        }
    }
}

void convertToLargeInteger(char *str, char *result) {
    result[0] = '\0';
    char buffer[5]; 
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        int asciiValue = (int)str[i];
        int bufferIndex = 0;

        do {
            buffer[bufferIndex++] = (asciiValue % 10) + '0';
            asciiValue /= 10;
        } while (asciiValue > 0);

        for (int j = bufferIndex - 1; j >= 0; j--) {
            result[index++] = buffer[j];
        }

        result[index] = '\0';
    }
}

char* addHalves(char *half1, char *half2, char *result) {
    int len1 = strlen(half1);
    int len2 = strlen(half2);

    printf("%s %s\n", half1, half2);
    int carry = 0, sum;

    int maxLen = len1 > len2 ? len1 : len2;
    result[maxLen + 1] = '\0';

    for (int i = 0; i < maxLen; i++) {
        int digit1 = i < len1 ? half1[len1 - i - 1] - '0' : 0;
        int digit2 = i < len2 ? half2[len2 - i - 1] - '0' : 0;

        printf("%d %d\n", digit1, digit2);

        sum = digit1 + digit2 + carry;
        result[maxLen - i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        result[0] = carry + '0';
    } else {
        for (int i = 0; i < maxLen; i++) {
            result[i] = result[i + 1];
        }
        result[maxLen] = '\0';
    }

    return result;
}

int main() {
    int *isPrime = (int *)malloc(10000 * sizeof(int));
    sieve(isPrime, 9999);

    char name[101], surname[101];
    printf("Enter your name: ");
    scanf("%100s", name);
    printf("Enter your surname: ");
    scanf("%100s", surname);

    char fullName[201] = "";
    strcat(fullName, name);
    strcat(fullName, surname);

    char largeInt[1001] = "";
    convertToLargeInteger(fullName, largeInt);
    printf("Converted large integer: %s\n", largeInt);

    int len = strlen(largeInt);
    int halfLen = len / 2;

    char half1[501], half2[501];
    strncpy(half1, largeInt, halfLen);
    half1[halfLen] = '\0';
    strcpy(half2, largeInt + halfLen);

    char sumOfHalves[1002] = "";
    addHalves(half1, half2, sumOfHalves);
    printf("Sum of halves: %s\n", sumOfHalves);

    printf("Remainders when divided by primes:\n");
    unsigned long long sum = strtoull(sumOfHalves, NULL, 10);
    int count = 0;
    for (int i = 1000; i <= 9999; i++) {
        if (isPrime[i]) {
            count++;
            printf("Remainder when divided by %d: %llu\n", i, sum % i);
        }

        if (count == 8) {
            break;
        }
    }

    free(isPrime);
    return 0;
}