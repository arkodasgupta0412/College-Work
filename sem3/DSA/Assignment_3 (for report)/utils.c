#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int top;
    char *arr;
    int capacity;
} Stack;

Stack *create(int);
int dispose(Stack *);
int is_empty(Stack *);
int is_full(Stack *);
int push(Stack *, char);
void pop(Stack *);
char top(Stack *);
int size(Stack *);
int capacity(Stack *);

// create, dispose, is_empty, is_full, push, pop, size, capacity
Stack *create(int size)
{
    /* Allocates memory for new stack creation based on input size */
    Stack *s;
    if ((s = (Stack *)malloc(sizeof(Stack))) != NULL)
    {
        s->capacity = size;
        if ((s->arr = (char *)malloc(s->capacity * sizeof(char))) == NULL)
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
    /* Returns true on successful dispose, else false */
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
    /* Returns 1 if empty stack, else 0 */
    return s->top == -1;
}

int is_full(Stack *s)
{
    /* Returns 1 if full stack, else 0 */
    return s->top == s->capacity - 1;
}

int push(Stack *s, char e)
{
    /* Returns true on successful push operation, else false */
    if (!is_full(s))
    {
        s->arr[++s->top] = e;
        return 1;
    }
    return 0;
}

void pop(Stack *s)
{
    /* Returns top element of stack on success, else '\0' */
    if (!is_empty(s))
    {
        s->arr[s->top--];
        return;
    }
    return;
}

char top(Stack *s)
{
    if (!is_empty(s))
    {
        return s->arr[s->top];
    }
    return '\0';
}

int size(Stack *s)
{
    /* Returns current size of stack */
    return s->top + 1;
}

int capacity(Stack *s)
{
    /* Returns max capacity of the stack */
    return s->capacity;
}
