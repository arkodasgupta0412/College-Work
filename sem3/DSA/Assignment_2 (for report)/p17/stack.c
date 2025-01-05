#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_s(Stack *st)
{
    /* initializes the stack, sets the top pointer to -1, indicates empty stack */
    st->top = -1;
}

int isFull(Stack *st)
{
    /* returns 1 if stack size = MAX_SIZE, else 0 */
    return (st->top >= MAX_SIZE - 1);
}

int isEmpty(Stack *st)
{
    /* returns 1 if stack is empty, else 0 */
    return (st->top == -1);
}

void push(Stack *st, char c)
{
    /* pushes new element onto stack, if stack not full */
    if (!isFull(st))
    {
        st->arr[++st->top] = c;
    }
    else
    {
        printf("Stack is full!\n");
    }
}

int pop(Stack *st)
{
    /* deletes and returns the topmost element of stack */
    if (!isEmpty(st))
    {
        return st->arr[st->top--];
    }
    else
    {
        printf("Stack is empty!\n");
    }
}

int top(Stack *st)
{
    /* displays the topmost element of stack */
    if (!isEmpty(st))
    {
        return st->arr[st->top];
    }
    else
    {
        printf("Stack is empty!\n");
    }
}
