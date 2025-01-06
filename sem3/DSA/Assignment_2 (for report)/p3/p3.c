/*
2.3. Define an ADT for List.
Write C data structure representation and functions for the operations on the List in a Header file with array
as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and include the
above header file. Two data structures with and without using sentinels in arrays are to be implemented.
*/


#include <stdio.h>
#include <stdlib.h>
#include "p3.h"

List *createList(int n)
{
    List *list = (List *)malloc(sizeof(List));
    list->capacity = n;
    list->size = 0;
    list->data = (int *)malloc(sizeof(list->capacity));
    return list;
}

void deleteList(List *list)
{
    free(list->data);
    free(list);
}

void print(List *list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int length(List *list)
{
    return list->size;
}

void rev(List **list)
{
    for (int i = 0; i < (*list)->size / 2; i++)
    {
        int t = (*list)->data[i];
        (*list)->data[i] = (*list)->data[(*list)->size - i - 1];
        (*list)->data[(*list)->size - i - 1] = t;
    }
}

int get(List *list, int pos)
{
    if (pos >= list->size)
        return -1;
    else
        return list->data[pos];
}

int search(List *list, int e)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->data[i] == e)
            return i;
    }
    return -1;
}

int modify(List *list, int pos, int val)
{
    if (pos >= list->size)
        return -1;
    else
    {
        list->data[pos] = val;
        return 0;
    }
}

int append(List *list, int val)
{
    if (list->size >= list->capacity)
        return -1;
    else
    {
        list->data[list->size] = val;
        list->size++;
        return 0;
    }
}

int insert(List *list, int pos, int val)
{
    if (list->size >= list->capacity)
        return -1;

    else
    {
        for (int i = list->size; i >= pos; i--)
        {
            list->data[i] = list->data[i - 1];
        }
        list->data[pos] = val;
        list->size++;
        return 0;
    }
}

int pop(List *list, int pos)
{
    if (pos >= list->size)
        return -1;

    else
    {
        int x = list->data[pos];
        for (int i = pos; i < list->size - 1; i++)
        {
            list->data[i] = list->data[i + 1];
        }
        list->size--;
        return x;
    }
}

int Remove(List *list, int val)
{
    int pos = search(list, val);
    if (pos == -1)
        return -1;
    else
    {
        int x = list->data[pos];
        for (int i = pos; i < list->size - 1; i++)
        {
            list->data[i] = list->data[i + 1];
        }
        list->size--;
        return x;
    }
}

void sort(List **list, int (*cmp)(int, int))
{
    for (int i = 0; i < (*list)->size; i++)
    {
        for (int j = 0; j < (*list)->size - i - 1; j++)
        {
            if (cmp((*list)->data[j], (*list)->data[j + 1]))
            {
                int t = (*list)->data[j];
                (*list)->data[j] = (*list)->data[j + 1];
                (*list)->data[j + 1] = t;
            }
        }
    }
}

int ascending(int a, int b)
{
    return a > b;
}

int descending(int a, int b)
{
    return a < b;
}

int main()
{
    List *list = NULL;
    int choice, size, pos, val, result;

    while (1)
    {
        printf("\nList Operations Menu:\n");
        printf("1. Create List\n");
        printf("2. Append Element\n");
        printf("3. Insert Element\n");
        printf("4. Delete Element at Position\n");
        printf("5. Remove Element by Value\n");
        printf("6. Get Element at Position\n");
        printf("7. Search Element\n");
        printf("8. Modify Element\n");
        printf("9. Print List\n");
        printf("10. Reverse List\n");
        printf("11. Sort List (Ascending)\n");
        printf("12. Sort List (Descending)\n");
        printf("13. List Length\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter list capacity: ");
            scanf("%d", &size);
            list = createList(&size);
            printf("List created with capacity %d\n", size);
            break;

        case 2:
            printf("Enter value to append: ");
            scanf("%d", &val);
            result = append(list, &val);
            if (result == 0)
                printf("Element appended successfully\n");
            else
                printf("List is full\n");
            break;

        case 3:
            printf("Enter position and value to insert: ");
            scanf("%d %d", &pos, &val);
            result = insert(list, &pos, &val);
            if (result == 0)
                printf("Element inserted successfully\n");
            else
                printf("Invalid position or list is full\n");
            break;

        case 4:
            printf("Enter position to delete: ");
            scanf("%d", &pos);
            result = pop(list, &pos);
            if (result != -1)
                printf("Deleted element: %d\n", result);
            else
                printf("Invalid position\n");
            break;

        case 5:
            printf("Enter value to remove: ");
            scanf("%d", &val);
            result = Remove(list, &val);
            if (result != -1)
                printf("Removed element: %d\n", result);
            else
                printf("Element not found\n");
            break;

        case 6:
            printf("Enter position: ");
            scanf("%d", &pos);
            result = get(list, &pos);
            if (result != -1)
                printf("Element at position %d: %d\n", pos, result);
            else
                printf("Invalid position\n");
            break;

        case 7:
            printf("Enter element to search: ");
            scanf("%d", &val);
            result = search(list, &val);
            if (result != -1)
                printf("Element found at position: %d\n", result);
            else
                printf("Element not found\n");
            break;

        case 8:
            printf("Enter position and new value: ");
            scanf("%d %d", &pos, &val);
            result = modify(list, &pos, &val);
            if (result == 0)
                printf("Element modified successfully\n");
            else
                printf("Invalid position\n");
            break;

        case 9:
            print(list);
            break;

        case 10:
            rev(&list);
            printf("List reversed\n");
            break;

        case 11:
            sort(&list, ascending);
            printf("List sorted in ascending order\n");
            break;

        case 12:
            sort(&list, descending);
            printf("List sorted in descending order\n");
            break;

        case 13:
            printf("List length: %d\n", length(list));
            break;

        case 14:
            deleteList(list);
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}