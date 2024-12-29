#ifndef P8CDLL_H
#define P8CDLL_H

#include <stdio.h>
#include <stdlib.h>

// Define a node for a non-zero element in the sparse matrix
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// initialize an empty list
Node *init_l();

// creates a new Linked List Node
Node *createNode(int);

// checks whether LL is empty or not
int empty_l(Node *);

// checks if current pointer points to end of list
int atend_l(Node *);

// inserts a new node target at front of LL
void insert_front(Node *, Node **);

// inserts a new node target after the node pointed to by prev
void insert_after(Node *, Node **);

// delete head of the linked list => assigns new head
void delete_front(Node **);

// deletes the node next to the node pointed by prev
void delete_after(Node **);

// prints the linked list
void print(Node *);

#endif // P8_H
