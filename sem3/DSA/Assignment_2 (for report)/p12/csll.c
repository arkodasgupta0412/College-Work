#include "csll.h"

// Initialize an empty list
Node *init_l()
{
    return NULL;
}

// Create a new node with given data
Node *createNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = node; // Point to itself, as it’s circular
    return node;
}

// Check if the list is empty
int empty_l(Node *head)
{
    return (head == NULL);
}

// Check if the given node is the last node (at end) in the list
int atend_l(Node *curr, Node *head)
{
    return (curr->next == head);
}

// Insert a node at the front of the list
void insert_front(Node *target, Node **head)
{
    if (*head == NULL)
    {
        *head = target;
        target->next = target; // Self-link as it's the only node
        return;
    }

    Node *cur = *head;
    while (cur->next != *head)
    {
        cur = cur->next;
    }
    cur->next = target; // Update the last node to point to the new front
    target->next = *head;
    *head = target;
}

// Insert a node after a given node
void insert_after(Node *target, Node **prev)
{
    if (*prev == NULL)
    {
        printf("Previous node is NULL; cannot insert\n");
        return;
    }
    target->next = (*prev)->next;
    (*prev)->next = target;
}

// Delete the front node of the list
void delete_front(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if ((*head)->next == *head)
    { // Only one node
        free(*head);
        *head = NULL;
        return;
    }

    Node *cur = *head;
    while (cur->next != *head)
    {
        cur = cur->next;
    }

    Node *temp = *head;
    cur->next = temp->next; // Update the last node to point to the new head
    *head = temp->next;     // Update head to the next node
    free(temp);
}

// Delete a node after the given node
void delete_after(Node **prev)
{
    if (*prev == NULL || (*prev)->next == NULL)
    {
        printf("No element to delete after the given node\n");
        return;
    }
    Node *temp = (*prev)->next;
    (*prev)->next = temp->next;
    free(temp);
}

// Print the list
/*void print(Node *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *temp = head;
    do
    {
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("HEAD\n");
}

// Main function demonstrating usage of the Circular Singly Linked List
int main()
{
    Node *l1 = init_l();

    Node *n1 = createNode(5);
    Node *n2 = createNode(10);
    Node *n3 = createNode(8);
    Node *n4 = createNode(3);
    Node *n5 = createNode(11);

    printf("Inserting nodes at the front:\n");
    insert_front(n1, &l1); // Insert n1 at the front
    print(l1);

    insert_after(n2, &n1); // Insert n2 after n1
    print(l1);

    insert_front(n3, &l1); // Insert n3 at the front
    print(l1);

    insert_after(n4, &n3); // Insert n4 after n3
    print(l1);

    insert_after(n5, &n1); // Insert n5 after n1
    print(l1);

    printf("\nDeleting front node:\n");
    delete_front(&l1); // Delete front node
    print(l1);

    printf("\nDeleting after a node:\n");
    delete_after(&n1); // Delete node after n1
    print(l1);

    return 0;
}*/
