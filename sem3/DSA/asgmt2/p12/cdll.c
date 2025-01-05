#include "cdll.h"

// Initialize an empty list
Node *init_l()
{
    return NULL; // Circular doubly linked list with NULL indicates an empty list
}

// Create a new Linked List Node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = newNode->next = NULL; // Initialize pointers to NULL
    return newNode;
}

// Check whether the linked list is empty
int empty_l(Node *head)
{
    return head == NULL;
}

// Check if the current pointer points to the end of the list
int atend_l(Node *current)
{
    return current == NULL;
}

// Insert a new node at the front of the list
void insert_front(Node *target, Node **head)
{
    if (empty_l(*head))
    {
        target->next = target->prev = target; // Single node points to itself
        *head = target;
    }
    else
    {
        Node *tail = (*head)->prev;
        target->next = *head;
        target->prev = tail;
        tail->next = target;
        (*head)->prev = target;
        *head = target; // Update head to new node
    }
}

// Insert a new node after the node pointed to by `prev`
void insert_after(Node *target, Node **prev)
{
    if (empty_l(*prev))
    {
        printf("Previous node cannot be NULL in a non-empty list\n");
        return;
    }
    Node *nextNode = (*prev)->next;
    target->next = nextNode;
    target->prev = *prev;
    (*prev)->next = target;
    nextNode->prev = target;
}

// Delete the head of the linked list and assign a new head
void delete_front(Node **head)
{
    if (empty_l(*head))
    {
        printf("List is already empty\n");
        return;
    }
    Node *toDelete = *head;
    if (toDelete->next == toDelete) // Single node in the list
    {
        free(toDelete);
        *head = NULL;
    }
    else
    {
        Node *tail = toDelete->prev;
        *head = toDelete->next;
        tail->next = *head;
        (*head)->prev = tail;
        free(toDelete);
    }
}

// Delete the node after the node pointed to by `prev`
void delete_after(Node **prev)
{
    if (empty_l(*prev) || (*prev)->next == *prev)
    {
        printf("Invalid operation: Either list is empty or there is no node to delete\n");
        return;
    }
    Node *toDelete = (*prev)->next;
    Node *nextNode = toDelete->next;

    (*prev)->next = nextNode;
    nextNode->prev = *prev;

    free(toDelete);
}

// Print the linked list
/*void print(Node *head)
{
    if (empty_l(head))
    {
        printf("List is empty\n");
        return;
    }
    Node *current = head;
    do
    {
        printf("%d->", current->data);
        current = current->next;
    } while (current != head);
    printf("HEAD\n");
}

int main()
{
    Node *head = init_l(); // Initialize an empty list

    // Insert nodes at the front of the list
    printf("Inserting 30, 20, and 10 at the front:\n");
    insert_front(createNode(10), &head);
    insert_front(createNode(20), &head);
    insert_front(createNode(30), &head);

    printf("Current list: ");
    print(head); // Expected: 30 20 10

    // Insert a node after the head
    printf("\nInserting 25 after the head:\n");
    insert_after(createNode(25), &head);
    printf("Current list: ");
    print(head); // Expected: 30 25 20 10

    // Delete the head node
    printf("\nDeleting the front node:\n");
    delete_front(&head);
    printf("Current list: ");
    print(head); // Expected: 25 20 10

    // Insert a node after the second node (20)
    printf("\nInserting 15 after the second node (20):\n");
    Node *second = head->next; // Second node
    insert_after(createNode(15), &second);
    printf("Current list: ");
    print(head); // Expected: 25 20 15 10

    // Delete the node after the head
    printf("\nDeleting the node after the head (20):\n");
    delete_after(&head);
    printf("Current list: ");
    print(head); // Expected: 25 15 10

    // Testing empty list
    printf("\nDeleting all nodes to test an empty list:\n");
    delete_front(&head);
    delete_front(&head);
    delete_front(&head);
    printf("Current list: ");
    print(head); // Expected: "List is empty"

    // Reinitialize and test single-node behavior
    printf("\nTesting single-node behavior:\n");
    insert_front(createNode(100), &head);
    printf("Current list: ");
    print(head); // Expected: 100

    delete_front(&head);
    printf("List after deleting the single node: ");
    print(head); // Expected: "List is empty"

    return 0;
}*/