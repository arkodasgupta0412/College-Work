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


#include "p8.h"
#include <stdio.h>

Node *init_l()
{
    return NULL;
}

Node *createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

int empty_l(Node *head)
{
    return (head == NULL);
}

int atend_l(Node *curr)
{
    return (curr->next == NULL);
}

void insert_front(Node *target, Node **head)
{
    target->next = (*head);
    *head = target;
}

void insert_after(Node *target, Node **prev)
{
    if ((*prev) == NULL)
    {
        printf("Previous node is NULL; cannot insert\n");
        return;
    }
    target->next = (*prev)->next;
    (*prev)->next = target;
}

void delete_front(Node **head)
{
    if (*head == NULL)
    {
        printf("List empty\n");
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_after(Node **prev)
{
    if ((*prev) == NULL || (*prev)->next == NULL)
    {
        printf("No element to delete after given node\n");
        return;
    }
    Node *temp = (*prev)->next;
    (*prev)->next = temp->next;
    free(temp);
}

/*void print(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main()
{
    // Initialize an empty linked list
    Node *l1 = init_l();
    printf("\nLinked list initialized (empty).\n");

    // Create nodes
    Node *n1 = createNode(5);
    Node *n2 = createNode(10);
    Node *n3 = createNode(8);
    Node *n4 = createNode(3);
    Node *n5 = createNode(11);
    printf("\nNodes created: 5, 10, 8, 3, 11.\n");

    // Insert node n1 (5) at the front
    insert_front(n1, &l1);
    printf("\nAfter inserting 5 at the front:\n");
    print(l1); // Expected output: 5 -> NULL

    // Insert node n2 (10) after node n1
    insert_after(n2, &n1);
    printf("\nAfter inserting 10 after 5:\n");
    print(l1); // Expected output: 5 -> 10 -> NULL

    // Insert node n3 (8) at the front
    insert_front(n3, &l1);
    printf("\nAfter inserting 8 at the front:\n");
    print(l1); // Expected output: 8 -> 5 -> 10 -> NULL

    // Insert node n4 (3) after node n3
    insert_after(n4, &n3);
    printf("\nAfter inserting 3 after 8:\n");
    print(l1); // Expected output: 8 -> 3 -> 5 -> 10 -> NULL

    // Insert node n5 (11) after node n1 (which now points to 5)
    insert_after(n5, &n1);
    printf("\nAfter inserting 11 after 5:\n");
    print(l1); // Expected output: 8 -> 3 -> 5 -> 11 -> 10 -> NULL

    // Delete the front node (8 in this case)
    delete_front(&l1);
    printf("\nAfter deleting the front node (8):\n");
    print(l1); // Expected output: 3 -> 5 -> 11 -> 10 -> NULL

    // Delete the node after node n5 (which is 10)
    delete_after(&n5);
    printf("\nAfter deleting the node after 11 (which is 10):\n");
    print(l1); // Expected output: 3 -> 5 -> 11 -> NULL

    return 0;
}*/
