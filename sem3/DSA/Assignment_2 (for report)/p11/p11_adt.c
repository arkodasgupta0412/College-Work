/*
2.11. Write all the above operations of Single Linked List for the implementation using array. You need to
develop Build_list and Build_list_reverse, as well as Print_list. 
*/


#include "p11_adt.h"

void init_l(NodePool *list)
{
    for (int i = 0; i < MAX - 1; i++)
    {
        list->next[i] = i + 1;
    }
    list->next[MAX - 1] = -1;
    list->head = -1;
    list->free = 0;
}

void insert_front(NodePool *list, int value)
{
    if (list->free == -1)
    {
        printf("List is full\n");
        return;
    }

    int newNode = list->free;
    list->free = list->next[newNode];
    list->data[newNode] = value;
    list->next[newNode] = list->head;
    list->head = newNode;
}

void insert_after(NodePool *list, int valpos, int newval)
{
    if (list->head == -1)
    {
        printf("List is empty. Cannot insert after a node in empty list\n");
        return;
    }

    if (list->free == -1)
    {
        printf("List is full. Cannot insert\n");
        return;
    }

    int temp = list->head;

    while (temp != -1 && list->data[temp] != valpos)
    {
        temp = list->next[temp];
    }

    if (temp == -1)
    {
        printf("Value not found in list\n");
        return;
    }

    int newNode = list->free;
    list->free = list->next[newNode];
    list->data[newNode] = newval;
    list->next[newNode] = list->next[temp];
    list->next[temp] = newNode;
}

void delete_front(NodePool *list)
{
    if (list->head == -1)
    {
        printf("List is empty\n");
        return;
    }
    int temp = list->head;
    list->head = list->next[temp];
    list->next[temp] = list->free;
    list->free = temp;
}

void delete_after(NodePool *list, int value)
{
    if (list->head == -1)
    {
        printf("List is empty. Cannot delete", value);
        return;
    }

    int temp = list->head;

    while (temp != -1 && list->data[temp] != value)
    {
        temp = list->next[temp];
    }

    if (temp == -1)
    {
        printf("Value not found in the list.\n", value);
        return;
    }

    int toDelete = list->next[temp];

    // If there is no node after the given value
    if (toDelete == -1)
    {
        printf("No node exists after value %d.\n", value);
        return;
    }

    list->next[temp] = list->next[toDelete];
    list->next[toDelete] = list->free;
    list->free = toDelete;
}

/* void printList(NodePool *list)
{
    if (list->head == -1)
    {
        printf("List is empty.\n");
        return;
    }

    int temp = list->head;
    while (temp != -1)
    {
        printf("%d -> ", list->data[temp]);
        temp = list->next[temp];
    }
    printf("NULL\n");
}

int main()
{
    NodePool list;
    init_l(&list);

    printf("=== Testing Linked List Operations ===\n");

    // Test insert_front
    printf("Inserting at the front: 10, 20, 30\n");
    insert_front(&list, 10);
    insert_front(&list, 20);
    insert_front(&list, 30);
    printList(&list);

    // Test insertAfter
    printf("Inserting 25 after 20:\n");
    insert_after(&list, 20, 25);
    printList(&list);

    // Test delete_front
    printf("Deleting the front node:\n");
    delete_front(&list);
    printList(&list);

    // Test delete_after
    printf("Deleting the node after 20:\n");
    delete_after(&list, 20);
    printList(&list);

    // Edge Case: Test delete_after when there is no node after
    printf("Trying to delete the node after 10 (no node):\n");
    delete_after(&list, 10);
    printList(&list);

    // Test delete_front until the list is empty
    printf("Deleting the front nodes until the list is empty:\n");
    delete_front(&list);
    printList(&list);
    delete_front(&list);
    printList(&list);
    delete_front(&list);

    // Test insertion after the list is empty
    printf("Rebuilding the list: Adding 40, 50\n");
    insert_front(&list, 40);
    insert_front(&list, 50);
    printList(&list);

    return 0;
}*/
