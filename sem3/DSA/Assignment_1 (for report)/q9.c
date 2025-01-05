/*
9. Write a program to check whether a given number is perfect. If it is a perfect number, add ‘97’ to
each of its digits. Now consider the result as an ASCII series. Convert the same into equivalent
character sequence.
Perfect Number is a Positive Integer (Greater Than Zero) whose divisor’s sum is equal to the number.
The Smallest perfect Number is 6.
Divisors of 6 are 1, 2 and 3. The sum of its Divisors is 1 + 2 +3 =6.
2 digit example = 28.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int getNumFromString(char str[]) {
    int i = 0;
    int num = 0;

    while (str[i] != '\0') {
        num = num * 10 + (int)(str[i] - '0');
        i++;
    }

    return num;
}


bool checkPerfect(int n) {
    int divisorSum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            divisorSum += i;
        }
    }

    if (divisorSum == n) {
        return true;
    }
    return false;
}


int main() {
    char arr[11];
    printf("Enter a number: ");
    scanf("%10s", arr);

    int num = getNumFromString(arr);

    if (checkPerfect(num)) {
        int i = 0;

        while (arr[i] != '\0') {
            arr[i] = arr[i] - '0' + 'a';
            i++;
        }

        printf("%s\n", arr);
    } else {
        printf("The number is not perfect!\n");
    }

    return 0;
}