#include <stdio.h>
#include <string.h>
#include "p8sll.c"
#define LEN 200

Node *createNumList(char num[])
{
    Node *head = init_l();

    for (int i = 0; i < strlen(num); i++)
    {
        insert_front(createNode(num[i] - '0'), &head);
    }
    return head;
}

void reverse(Node **head)
{
    Node *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void toString(Node *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }

    // Temporary stack-based storage for digits
    char temp[LEN] = {0};
    int index = 0;

    while (head)
    {
        temp[index++] = head->data + '0'; // Convert int to char and store in temp
        head = head->next;
    }

    // Print digits in reverse order (as the list stores them in reverse)
    for (int i = index - 1; i >= 0; i--)
    {
        putchar(temp[i]);
    }
    putchar('\n'); // End the number output with a new line
}

Node *add(Node *n1, Node *n2)
{
    Node *sum = init_l(), *t1 = n1, *t2 = n2;
    int carry = 0, s;

    while (t1 != NULL && t2 != NULL)
    {
        s = (t1->data + t2->data + carry) % 10;
        insert_front(createNode(s), &sum);

        carry = (t1->data + t2->data + carry) / 10;
        t1 = t1->next;
        t2 = t2->next;
    }

    while (t1 != NULL)
    {
        s = (t1->data + carry) % 10;
        insert_front(createNode(s), &sum);
        carry = (t1->data + carry) / 10;
        t1 = t1->next;
    }

    while (t2 != NULL)
    {
        s = (t2->data + carry) % 10;
        insert_front(createNode(s), &sum);
        carry = (t2->data + carry) / 10;
        t2 = t2->next;
    }

    if (carry)
    {
        insert_front(createNode(carry), &sum);
    }

    reverse(&sum);
    return sum;
}

Node *subtract(Node *n1, Node *n2)
{
    Node *result = init_l();
    Node *t1 = n1, *t2 = n2;
    int borrow = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int digit1 = t1 ? t1->data : 0;
        int digit2 = t2 ? t2->data : 0;

        // Apply borrow if needed
        digit1 -= borrow;

        if (digit1 < digit2)
        {
            digit1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int diff = digit1 - digit2;
        insert_front(createNode(diff), &result);

        if (t1)
            t1 = t1->next;
        if (t2)
            t2 = t2->next;
    }

    // Remove leading zeros in result
    while (result && result->data == 0)
    {
        Node *temp = result;
        result = result->next;
        free(temp);
    }

    reverse(&result);

    return result ? result : createNode(0); // Return 0 if result is empty
}

Node *multiply(Node *n1, Node *n2)
{
    if (!n1 || !n2)
        return createNode(0); // Return 0 if any number is missing

    Node *result = init_l();
    Node *t1 = n1, *t2 = n2;

    // Initialize the result array to store intermediate sums
    for (int i = 0; i < LEN; i++)
        insert_front(createNode(0), &result);

    Node *result_iter = result;
    int pos = 0;

    while (t2)
    {
        Node *result_temp = result_iter;
        int carry = 0;
        t1 = n1;

        while (t1)
        {
            int product = t1->data * t2->data + carry + result_temp->data;
            result_temp->data = product % 10; // Update result node with current value
            carry = product / 10;             // Compute carry
            t1 = t1->next;
            result_temp = result_temp->next;
        }

        // Add leftover carry to the next node
        while (carry > 0)
        {
            int sum = carry + result_temp->data;
            result_temp->data = sum % 10;
            carry = sum / 10;
            result_temp = result_temp->next;
        }

        // Move result pointer one step to handle the next digit in t2
        result_iter = result_iter->next;
        t2 = t2->next;
        pos++;
    }

    // Remove leading zeros
    Node *prev = NULL;
    reverse(&result);
    while (result && result->data == 0)
    {
        prev = result;
        result = result->next;
        free(prev);
    }
    reverse(&result);

    return result ? result : createNode(0); // Return the resulting product
}

int main()
{
    char num1[LEN], num2[LEN];
    printf("Enter large number 1: ");
    scanf("%s", num1);
    printf("Enter large number 2: ");
    scanf("%s", num2);

    Node *n1 = createNumList(num1);
    Node *n2 = createNumList(num2);

    printf("X = ");
    toString(n1);
    printf("Y = ");
    toString(n2);

    Node *sum = add(n1, n2);
    Node *diff = subtract(n1, n2);
    Node *prod = multiply(n1, n2);

    printf("Sum: X + Y = ");
    toString(sum);

    printf("Difference: X - Y = ");
    toString(diff);

    printf("Product: X * Y = ");
    toString(prod);

    return 0;
}