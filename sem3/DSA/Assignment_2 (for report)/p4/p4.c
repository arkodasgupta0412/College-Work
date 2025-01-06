/*
2.4. Define an ADT for Set.
Write C data representation and functions for the operations on the Set in a Header file, with array as the
base data structure.
Write a menu-driven main program in a separate file for testing the different operations and include the
above header file
*/


#include <stdio.h>
#include <stdlib.h>
#include "p4.h"

Set *createSet(int n)
{
    Set *set = (Set *)malloc(sizeof(Set));
    set->capacity = n;
    set->size = 0;
    set->data = (int *)malloc(n * sizeof(int));

    return set;
}

void deleteSet(Set *s)
{
    free(s->data);
    free(s);
}

void print(Set *s)
{
    for (int i = 0; i < s->size; i++)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

int size(Set *s)
{
    return s->size;
}

int max_size(Set *s)
{
    return s->capacity;
}

int empty(Set *s)
{
    return (s->size == 0);
}

int insert(Set *s, int key)
{
    if (find(s, key) == s->size)
    {
        int pos = upper_bound(s, key);
        if (s->capacity > s->size)
        {
            for (int i = s->size - 1; i >= pos; i--)
            {
                s->data[i + 1] = s->data[i];
            }
            s->data[pos] = key;
            s->size++;
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

int erase(Set *s, int key)
{
    int pos = find(s, key);
    if (pos != s->size)
    {
        for (int i = pos; i < s->size; i++)
        {
            s->data[i] = s->data[i + 1];
        }
        s->size--;
    }
    return 0;
}

void clear(Set *s)
{
    free(s->data);
    s->size = 0;
}

int find(Set *s, int key)
{
    int low = 0, high = s->size - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (s->data[mid] == key)
            return mid;
        if (s->data[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return s->size;
}

int count(Set *s, int key)
{
    for (int i = 0; i < s->size; i++)
    {
        if (s->data[i] == key)
            return 1;
    }
    return 0;
}

int lower_bound(Set *s, int key)
{
    int low = 0, high = s->size;
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (s->data[mid] >= key)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}

int upper_bound(Set *s, int key)
{
    int low = 0, high = s->size;
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (s->data[mid] > key)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}

int main()
{
    Set *set = NULL;
    int choice, capacity, key, result;

    while (1)
    {
        printf("\nSet Operations Menu:\n");
        printf("1. Create Set\n");
        printf("2. Insert Element\n");
        printf("3. Erase Element\n");
        printf("4. Find Element\n");
        printf("5. Count Element\n");
        printf("6. Lower Bound\n");
        printf("7. Upper Bound\n");
        printf("8. Print Set\n");
        printf("9. Size\n");
        printf("10. Max Size\n");
        printf("11. Check if Empty\n");
        printf("12. Clear Set\n");
        printf("13. Delete Set and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter set capacity: ");
            scanf("%d", &capacity);
            set = createSet(&capacity);
            printf("Set created with capacity %d\n", capacity);
            break;

        case 2:
            printf("Enter element to insert: ");
            scanf("%d", &key);
            result = insert(set, &key);
            if (result)
                printf("Element %d inserted successfully\n", key);
            else
                printf("Element %d already exists or set is full\n", key);
            break;

        case 3:
            printf("Enter element to erase: ");
            scanf("%d", &key);
            erase(set, &key);
            printf("Element erased if it existed\n");
            break;

        case 4:
            printf("Enter element to find: ");
            scanf("%d", &key);
            result = find(set, &key);
            if (result != set->size)
                printf("Element found at position %d\n", result);
            else
                printf("Element not found\n");
            break;

        case 5:
            printf("Enter element to count: ");
            scanf("%d", &key);
            result = count(set, &key);
            printf("Count of element: %d\n", result);
            break;

        case 6:
            printf("Enter element for lower bound: ");
            scanf("%d", &key);
            result = lower_bound(set, &key);
            printf("Lower bound position: %d\n", result);
            break;

        case 7:
            printf("Enter element for upper bound: ");
            scanf("%d", &key);
            result = upper_bound(set, &key);
            printf("Upper bound position: %d\n", result);
            break;

        case 8:
            printf("Set elements: ");
            print(set);
            break;

        case 9:
            printf("Current size: %d\n", size(set));
            break;

        case 10:
            printf("Maximum size: %d\n", max_size(set));
            break;

        case 11:
            if (empty(set))
                printf("Set is empty\n");
            else
                printf("Set is not empty\n");
            break;

        case 12:
            clear(set);
            printf("Set cleared\n");
            break;

        case 13:
            deleteSet(set);
            printf("Set deleted. Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}