/* Infix expression to postfix expression conversion */

#include <stdio.h>
#include "utils.c"

void infixToPostfix(char[], int);
int priority(char);
void printExp(char[]);

int main()
{
    char infix[100];
    printf("Enter fully parenthesized infix expression. Press Enter to stop.\n");
    char c;
    int i = 0;

    do
    {
        scanf("%c", &c);
        infix[i++] = c;

    } while (c != '\n');
    infix[i] = '#';

    int size = sizeof(infix) / sizeof(char);

    printf("\nInfix Expression:\n");
    printExp(infix);
    printf("Postfix Expression:\n");
    infixToPostfix(infix, size);

    return 0;
}

void infixToPostfix(char infix[], int size)
{
    Stack *st = create(size);
    char postfix[size];
    int j = 0;

    for (int i = 0; infix[i] != '#'; i++)
    {
        char c = infix[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
            postfix[j++] = c;
        }

        else if (c == '(')
        {
            push(st, c);
        }

        else if (c == ')')
        {
            while (top(st) != '(')
            {
                postfix[j++] = top(st);
                pop(st);
            }
            pop(st);
        }

        else
        {
            while (!is_empty(st) && priority(c) <= priority(top(st)))
            {
                postfix[j++] = top(st);
                pop(st);
            }
            push(st, c);
        }
    }

    postfix[j] = '#';

    printExp(postfix);
}

int priority(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

void printExp(char exp[])
{
    for (int i = 0; exp[i] != '#'; i++)
    {
        printf("%c ", exp[i]);
    }
    printf("\n");
}