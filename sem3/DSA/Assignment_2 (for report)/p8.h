/*
2.8. Implement the following functions of ADT Linked List using singly linked list as a header file:
init_l(cur) – initialize a list
empty_l(head) – boolean function to return true if list pointed to by head is empty
atend_l(cur) – boolean function to return true if cur points to the last node in the list
insert_front(target, head) – insert the node pointed to by target as the first node of the list pointed to by
head
insert_after(target, prev) – insert the node pointed to by target after the node pointed to by prev
delete_front(head) – delete the first element of the list pointed to by head
delete_after(prev) – delete the node after the one pointed to by prev
*/


#ifndef P8
#define P8

#include <stdio.h>
#include <stdlib.h>

// Define a node for a non-zero element in the sparse matrix
typedef struct Node
{
    int data;
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
