/*
3.2 Define the ADTs for Stack and Queue.
a) Implement the ADTS using Array.
b) Implement the ADTs using Linked List. Use the data structures for Linked
List already developed in Assignment II as header files.
c) Develop a program for converting a string containing an infix expression to a
string containing the corresponding postfix expression. Both the strings are
terminated by a sentinel ‘#’.
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int top;
    int *arr;
    int capacity;
} Stack;

Stack *create(int);
int dispose(Stack *);
int is_empty(Stack *);
int is_full(Stack *);
int push(Stack *, int);
int pop(Stack *);

// create, dispose, is_empty, is_full, push, pop, size, capacity
Stack *create(int size)
{
    /* allocates memory for new stack creation based on input size */
    Stack *s;
    if ((s = (Stack *)malloc(sizeof(Stack))) != NULL)
    {
        s->capacity = size;
        if ((s->arr = (int *)malloc(s->capacity * sizeof(int))) == NULL)
        {
            printf("Stack container allocation error!\n");
        }
        s->top = -1;
        return s;
    }
    else
    {
        printf("Memory allocation error!\n");
        exit(0);
    }
}

int dispose(Stack *s)
{
    /* returns true on successful dispose, else false */
    if (s != NULL)
    {
        free(s->arr);
        free(s);
        return 1;
    }
    return 0;
}

int is_empty(Stack *s)
{
    /* returns 1 is empty stack, else 0 */
    return s->top == -1;
}

int is_full(Stack *s)
{
    /* returns 1 if full stack, else 0 */
    return s->top == s->capacity - 1;
}

int push(Stack *s, int e)
{
    /* returns true on successful push operation, else false */
    if (!is_full(s))
    {
        s->arr[++s->top] = e;
        // printf("%d\n", s->top);
        return 1;
    }
    return 0;
}

int pop(Stack *s)
{
    /* returns top element of stack on success, else -1 */
    if (!is_empty(s))
    {
        int x = s->arr[s->top--];
        // printf("%d\n", s->top);
        return x;
    }
    return -1;
}

int size(Stack *s)
{
    /* returns current size of stack */
    return s->top + 1;
}

int capacity(Stack *s)
{
    /* returns max capacity of the stack */
    return s->capacity;
}
