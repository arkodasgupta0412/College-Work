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
#include "../../Assignment_2/p12/p12csll.c"

typedef struct Queue
{
    Node *rear;
    Node *front;
} Queue;

Queue *create(void);
void dispose(Queue *);
int is_empty(Queue *);
void enqueue(Queue *, int);
int dequeue(Queue *s);

Queue *create()
{
    Queue *q;
    q->rear = NULL;
    q->front = NULL;
    return q;
}

void dispose(Queue *q)
{
    if (q != NULL)
    {
        free(q->rear);
        free(q->front);
        free(q);
    }
}

int is_empty(Queue *q)
{
    return (q->front == NULL & q->rear == NULL);
}

void push(Queue *q, int data)
{
    Node *newnode = createNode(data);
    if (is_empty(q))
    {
        insert_front(newnode, &q->front);
        q->front = newnode;
        q->rear = newnode;
    }
    else
    {
        insert_after(newnode, &q->rear);
        q->rear = newnode;
    }
}

int pop(Queue *q)
{
    if (is_empty(q))
    {
        return -1;
    }

    else if (q->front == q->rear)
    {
        int x = q->front->data;
        delete_front(&q->front);
        q->rear = NULL;
        return x;
    }
    else
    {
        int x = q->front->data;
        delete_front(&q->front);
        return x;
    }
}