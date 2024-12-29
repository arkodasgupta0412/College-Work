#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{
    int front, rear, capacity;
    int *arr;
} Queue;

Queue *create(int);
int dispose(Queue *);
int is_empty(Queue *);
int is_full(Queue *);
int push(Queue *, int);
int pop(Queue *);

// create, dispose, is_empty, is_full, enqueue, dequeue, size, capacity
Queue *create(int size)
{
    /* allocates memory for new queue creation based on input size */
    Queue *q;
    if ((q = (Queue *)malloc(sizeof(Queue))) != NULL)
    {
        q->capacity = size;
        if ((q->arr = (int *)malloc(q->capacity * sizeof(int))) == NULL)
        {
            printf("Stack container allocation error!\n");
        }
        q->front = -1, q->rear = -1;
        return q;
    }
    else
    {
        printf("Memory allocation error!\n");
        exit(0);
    }
}

int dispose(Queue *q)
{
    /* returns true on successful dispose, else false */
    if (q != NULL)
    {
        free(q->arr);
        free(q);
        return 1;
    }
    return 0;
}

int is_empty(Queue *q)
{
    /* returns 1 is empty queue, else 0 */
    if (q->front == q->rear)
    {
        q->front = -1, q->rear = -1;
        return 1;
    }
    return 0;
}

int is_full(Queue *q)
{
    /* returns 1 if full queue, else 0 */
    return q->rear == q->capacity - 1;
}

int enqueue(Queue *q, int e)
{
    /* returns true on successful push operation, else false */
    if (!is_full(q))
    {
        q->arr[++q->rear] = e;
        return 1;
    }
    return 0;
}

int dequeue(Queue *q)
{
    /* returns top element of stack on success, else -1 */
    if (!is_empty(q))
    {
        int x = q->arr[++q->front];
        return x;
    }
    return -1;
}

int size(Queue *q)
{
    /* returns current size of squeue */
    return q->rear - q->front;
}

int capacity(Queue *q)
{
    /* returns max capacity of the queue */
    return q->capacity;
}
