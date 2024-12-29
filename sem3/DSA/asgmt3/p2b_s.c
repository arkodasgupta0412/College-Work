#include <stdio.h>
#include "../asgmt2/p8sll.c"

typedef struct Stack
{
    Node *top;
    Node *head;
} Stack;

Stack *create(void);
void dispose(Stack *);
int is_empty(Stack *);
void push(Stack *, int);
int pop(Stack *s);

Stack *create()
{
    Stack *s;
    s->head = NULL;
    s->top = s->head;
    return s;
}

void dispose(Stack *s)
{
    if (s != NULL)
    {
        free(s->top);
        free(s->head);
        free(s);
    }
}

int is_empty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, int data)
{
    Node *newnode = createNode(data);
    if (s->top == NULL)
    {
        insert_front(newnode, &s->head);
        s->top = s->head;
    }
    else
    {
        insert_after(newnode, &s->top);
        s->top = newnode;
    }
}

int pop(Stack *s)
{
    if (s->head == NULL)
    {
        return -1;
    }

    else if (s->top == s->head)
    {
        int x = s->top->data;
        delete_front(&s->top);
        s->head = NULL;
        s->top = s->head;
        return x;
    }
    else
    {
        int x = s->top->data;
        Node *cur = s->head;
        while (cur->next != s->top)
        {
            cur = cur->next;
        }
        delete_after(&cur);
        s->top = cur;
        return x;
    }
}