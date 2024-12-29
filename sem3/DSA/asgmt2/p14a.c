#include <stdio.h>
#include <string.h>
#define LEN 200
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void createArray(char num[], int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        arr[i] = num[i] - '0';
    }
}

void add(int arr1[], int arr2[], int len1, int len2, int sum[])
{
    int i = len1 - 1, j = len2 - 1, k = MAX(len1, len2), carry = 0;

    while (i >= 0 && j >= 0)
    {
        int y = arr1[i] + arr2[j] + carry;
        sum[k--] = y % 10;
        carry = y / 10;
        i--;
        j--;
    }

    while (i >= 0)
    {
        int y = arr1[i] + carry;
        sum[k--] = y % 10;
        carry = y / 10;
        i--;
    }

    while (j >= 0)
    {
        int y = arr2[j] + carry;
        sum[k--] = y % 10;
        carry = y / 10;
        j--;
    }

    if (carry)
    {
        sum[0] = carry;
    }
}

void sub(int arr1[], int arr2[], int len1, int len2, int diff[])
{
    int i = len1 - 1, j = len2 - 1, k = len1 - 1, borrow = 0;

    while (i >= 0)
    {
        int x = arr1[i] - borrow;
        int y = (j >= 0) ? arr2[j] : 0;

        if (x < y)
        {
            x += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff[k--] = x - y;
        i--;
        j--;
    }
}

void multiply(int arr1[], int arr2[], int len1, int len2, int product[])
{
    int temp[len1 + len2];
    memset(temp, 0, sizeof(temp)); // Initialize all elements to zero

    for (int i = len1 - 1; i >= 0; i--)
    {
        for (int j = len2 - 1; j >= 0; j--)
        {
            int mul = arr1[i] * arr2[j];
            int pos1 = i + j, pos2 = i + j + 1;

            int sum = mul + temp[pos2];
            temp[pos2] = sum % 10;
            temp[pos1] += sum / 10;
        }
    }

    memcpy(product, temp, sizeof(temp)); // Copy results to product
}

void print(int arr[], int len)
{
    int leadingZero = 1; // To skip leading zeros
    for (int i = 0; i < len; i++)
    {
        if (leadingZero && arr[i] == 0)
            continue;
        leadingZero = 0;
        printf("%d", arr[i]);
    }
    if (leadingZero)
        printf("0"); // If all zeros, print one 0
    printf("\n");
}

int main()
{
    char num1[LEN], num2[LEN];
    printf("Enter large number 1: ");
    scanf("%s", num1);
    printf("Enter large number 2: ");
    scanf("%s", num2);

    int len1 = strlen(num1), len2 = strlen(num2);
    int digit1[len1], digit2[len2];

    createArray(num1, digit1, len1);
    createArray(num2, digit2, len2);

    int sum[MAX(len1, len2) + 1];
    memset(sum, 0, sizeof(sum));
    add(digit1, digit2, len1, len2, sum);
    printf("Sum: ");
    print(sum, MAX(len1, len2) + 1);

    // Subtraction
    if (len1 > len2 || (len1 == len2 && strcmp(num1, num2) >= 0))
    {
        int diff[len1];
        memset(diff, 0, sizeof(diff));
        sub(digit1, digit2, len1, len2, diff);
        printf("Difference: ");
        print(diff, len1);
    }
    else
    {
        int diff[len2];
        memset(diff, 0, sizeof(diff));
        sub(digit2, digit1, len2, len1, diff);
        printf("Difference: -");
        print(diff, len2);
    }

    // Multiplication
    int product[len1 + len2];
    memset(product, 0, sizeof(product));
    multiply(digit1, digit2, len1, len2, product);
    printf("Product: ");
    print(product, len1 + len2);

    return 0;
}