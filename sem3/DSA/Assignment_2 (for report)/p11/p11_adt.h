/*
2.11. Write all the above operations of Single Linked List for the implementation using array. You need to
develop Build_list and Build_list_reverse, as well as Print_list. 
*/


#ifndef P11_ADT_H
#define P11_ADT_H

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct NodePool
{
    int data[MAX]; // storing values
    int next[MAX]; // storing links
    int head;      // storing starting element, (-1 if empty)
    int free;      // next free space to insert
} NodePool;

void init_l(NodePool *);
void insert_front(NodePool *, int);
void insert_after(NodePool *, int, int);
void delete_front(NodePool *);
void delete_after(NodePool *, int);
void printList(NodePool *);

#endif