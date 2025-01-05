#ifndef STACK_H
#define STACK_H
#define MAX_SIZE 100

typedef struct Stack
{
    char arr[MAX_SIZE];
    int top;
} Stack;

void init_s(Stack *);
int isFull(Stack *);
int isEmpty(Stack *st);
void push(Stack *, char);
int pop(Stack *);
int top(Stack *);

#endif