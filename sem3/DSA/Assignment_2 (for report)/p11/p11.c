/*
2.11. Write all the above operations of Single Linked List for the implementation using array. You need to
develop Build_list and Build_list_reverse, as well as Print_list. 
*/


#include "p11_adt.c"
#include <stdio.h>

void print_list(NodePool *list);
void print_reverse_list(NodePool *list);
int find_size(NodePool *list);
int are_equal(NodePool *list1, NodePool *list2);
int search_and_delete(NodePool *list, int key);
void append_list(NodePool *list1, NodePool *list2);
void delete_nth_node(NodePool *list, int n);
int is_ordered(NodePool *list);
void merge_sorted_lists(NodePool *list1, NodePool *list2, NodePool *result);
void remove_duplicates(NodePool *list, int is_sorted);
void swap_pairwise(NodePool *list);
void move_last_to_front(NodePool *list);
void delete_alternate_nodes(NodePool *list);
void rotate_list(NodePool *list, int n);
void reverse_list(NodePool *list);
void sort_list(NodePool *list);
void build_reverse_list(NodePool *list, int arr[], int size);

void menu()
{
    // Menu for the linked list operations
    printf("\nLinked List Operations Menu:\n");
    printf("1. Insert at front\n");
    printf("2. Insert after a node\n");
    printf("3. Delete at front\n");
    printf("4. Delete after a node\n");
    printf("5. Print list\n");
    printf("6. Print reverse list\n");
    printf("7. Find size of list\n");
    printf("8. Check if lists are equal\n");
    printf("9. Search and delete node\n");
    printf("10. Merge two sorted lists\n");
    printf("11. Append list to the end of another list\n");
    printf("12. Delete nth node\n");
    printf("13. Delete last node\n");
    printf("14. Delete first node\n");
    printf("15. Check if list is ordered\n");
    printf("16. Sort list\n");
    printf("17. Reverse list\n");
    printf("18. Rotate list\n");
    printf("19. Remove duplicates\n");
    printf("20. Exit\n");
}

int main()
{
    NodePool list1, list2, result;
    init_l(&list1);
    init_l(&list2);
    init_l(&result);

    int choice, value, valpos, n, key;

    menu();

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: // Insert at front
            printf("Enter value to insert at front: ");
            scanf("%d", &value);
            insert_front(&list1, value);
            printf("Value inserted\n");
            break;

        case 2: // Insert after a node
            printf("Enter value after which to insert: ");
            scanf("%d", &valpos);
            printf("Enter new value to insert: ");
            scanf("%d", &value);
            insert_after(&list1, valpos, value);
            printf("Value inserted\n");
            break;

        case 3: // Delete at front
            delete_front(&list1);
            printf("Value deleted\n");
            break;

        case 4: // Delete after a node
            printf("Enter value after which to delete: ");
            scanf("%d", &value);
            delete_after(&list1, value);
            printf("Value deleted\n");
            break;

        case 5: // Print list
            printf("Printing list:\n");
            print_list(&list1);
            break;

        case 6: // Print reverse list
            printf("Printing reverse list:\n");
            print_reverse_list(&list1);
            break;

        case 7: // Find size of the list
            printf("Size of the list: %d\n", find_size(&list1));
            break;

        case 8: // Check if lists are equal
            if (are_equal(&list1, &list2))
            {
                printf("Lists are equal.\n");
            }
            else
            {
                printf("Lists are not equal.\n");
            }
            break;

        case 9: // Search and delete node
            printf("Enter key to search and delete: ");
            scanf("%d", &key);
            search_and_delete(&list1, key);
            break;

        case 10: // Merge two sorted lists
            merge_sorted_lists(&list1, &list2, &result);
            printf("Merged lists:\n");
            print_list(&result);
            break;

        case 11: // Append list2 at the end of list1
            append_list(&list1, &list2);
            break;

        case 12: // Delete nth node
            printf("Enter the position of the node to delete: ");
            scanf("%d", &n);
            delete_nth_node(&list1, n);
            break;

        case 13: // Delete last node
            delete_nth_node(&list1, find_size(&list1));
            break;

        case 14: // Delete first node
            delete_nth_node(&list1, 1);
            break;

        case 15: // Check if the list is ordered
            if (is_ordered(&list1))
            {
                printf("The list is ordered.\n");
            }
            else
            {
                printf("The list is not ordered.\n");
            }
            break;

        case 16: // Sort list
            sort_list(&list1);
            printf("List sorted:\n");
            print_list(&list1);
            break;

        case 17: // Reverse list
            reverse_list(&list1);
            printf("List reversed:\n");
            print_list(&list1);
            break;

        case 18: // Rotate list
            printf("Enter shift: ");
            scanf("%d", &n);
            rotate_list(&list1, n);
            printf("List rotated:\n");
            print_list(&list1);
            break;

        case 19: // Remove duplicates
            remove_duplicates(&list1, is_ordered(&list1));
            printf("Duplicates removed:\n");
            print_list(&list1);
            break;

        case 20: // Exit
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            printf("Enter 'm' to display menu again\n");
            char showMenu;
            scanf(" %c", &showMenu);
            if (showMenu == 'm' || showMenu == 'M')
            {
                menu();
            }
            break;
        }
    }

    return 0;
}

void print_list(NodePool *list)
{
    int temp = list->head;
    while (temp != -1)
    {
        printf("%d -> ", list->data[temp]);
        temp = list->next[temp];
    }
    printf("NULL\n");
}

void print_reverse(NodePool *list, int temp)
{
    if (temp == -1)
        return;
    print_reverse(list, list->next[temp]);
    printf("%d -> ", list->data[temp]);
}

void print_reverse_list(NodePool *list)
{
    if (list->head == -1)
    {
        printf("List is empty.\n");
        return;
    }
    print_reverse(list, list->head);
    printf("NULL\n");
}

int find_size(NodePool *list)
{
    int count = 0, temp = list->head;
    while (temp != -1)
    {
        count++;
        temp = list->next[temp];
    }
    return count;
}

int are_equal(NodePool *list1, NodePool *list2)
{
    int temp1 = list1->head, temp2 = list2->head;
    while (temp1 != -1 && temp2 != -1)
    {
        if (list1->data[temp1] != list2->data[temp2])
            return 0;
        temp1 = list1->next[temp1];
        temp2 = list2->next[temp2];
    }
    return (temp1 == -1 && temp2 == -1);
}

int search_and_delete(NodePool *list, int key)
{
    if (list->head == -1)
        return 0;

    if (list->data[list->head] == key)
    {
        delete_front(list);
        return 1;
    }

    int temp = list->head;
    while (list->next[temp] != -1 && list->data[list->next[temp]] != key)
    {
        temp = list->next[temp];
    }

    if (list->next[temp] == -1)
        return 0;

    delete_after(list, list->data[temp]);
    return 1;
}

void append_list(NodePool *list1, NodePool *list2)
{
    if (list2->head == -1)
        return;
    if (list1->head == -1)
    {
        list1->head = list2->head;
        list1->free = list2->free;
        return;
    }

    int temp = list1->head;
    while (list1->next[temp] != -1)
    {
        temp = list1->next[temp];
    }
    list1->next[temp] = list2->head;
}

void delete_nth_node(NodePool *list, int n)
{
    if (n <= 0)
    {
        printf("Invalid position.\n");
        return;
    }

    if (n == 1)
    {
        delete_front(list);
        return;
    }

    int temp = list->head, count = 1;
    while (temp != -1 && count < n - 1)
    {
        temp = list->next[temp];
        count++;
    }

    if (temp == -1 || list->next[temp] == -1)
    {
        printf("Position exceeds list size.\n");
        return;
    }

    delete_after(list, list->data[temp]);
}

int is_ordered(NodePool *list)
{
    int temp = list->head;
    while (temp != -1 && list->next[temp] != -1)
    {
        if (list->data[temp] > list->data[list->next[temp]])
            return 0;
        temp = list->next[temp];
    }
    return 1;
}

void merge_sorted_lists(NodePool *list1, NodePool *list2, NodePool *result)
{
    if (!is_ordered(list1) || !is_ordered(list2))
    {
        printf("Both lists must be sorted.\n");
        return;
    }

    int temp1 = list1->head, temp2 = list2->head;

    while (temp1 != -1 && temp2 != -1)
    {
        if (list1->data[temp1] < list2->data[temp2])
        {
            insert_front(result, list1->data[temp1]);
            temp1 = list1->next[temp1];
        }
        else
        {
            insert_front(result, list2->data[temp2]);
            temp2 = list2->next[temp2];
        }
    }

    while (temp1 != -1)
    {
        insert_front(result, list1->data[temp1]);
        temp1 = list1->next[temp1];
    }

    while (temp2 != -1)
    {
        insert_front(result, list2->data[temp2]);
        temp2 = list2->next[temp2];
    }
}

void insert_target_node(NodePool *list, int target, int value, int position)
{
    if (position == 0)
    {
        insert_front(list, value);
        return;
    }

    int temp = list->head;
    while (temp != -1 && list->data[temp] != target)
    {
        temp = list->next[temp];
    }

    if (temp == -1)
    {
        printf("Target node not found.\n");
        return;
    }

    if (position == 1)
    {
        insert_after(list, list->data[temp], value);
    }
    else
    {
        printf("Unsupported position for target node insertion.\n");
    }
}

void remove_duplicates(NodePool *list, int is_sorted)
{
    if (list->head == -1)
        return;

    int current = list->head;
    while (current != -1 && list->next[current] != -1)
    {
        int nextNode = list->next[current];

        if (is_sorted)
        {
            while (nextNode != -1 && list->data[nextNode] == list->data[current])
            {
                delete_after(list, list->data[current]);
                nextNode = list->next[current];
            }
        }
        else
        {
            int prev = current;
            while (nextNode != -1)
            {
                if (list->data[nextNode] == list->data[current])
                {
                    delete_after(list, list->data[prev]);
                }
                else
                {
                    prev = nextNode;
                }
                nextNode = list->next[nextNode];
            }
        }
        current = list->next[current];
    }
}

void swap_pairwise(NodePool *list)
{
    if (list->head == -1 || list->next[list->head] == -1)
        return;

    int temp = list->head;
    while (temp != -1 && list->next[temp] != -1)
    {
        int first = temp;
        int second = list->next[temp];

        // Swap the values
        int tempValue = list->data[first];
        list->data[first] = list->data[second];
        list->data[second] = tempValue;

        // Move to the next pair
        temp = list->next[list->next[first]];
    }
}

void move_last_to_front(NodePool *list)
{
    if (list->head == -1 || list->next[list->head] == -1)
        return;

    int temp = list->head;
    while (list->next[list->next[temp]] != -1)
    {
        temp = list->next[temp];
    }

    int lastNode = list->next[temp];

    // Remove the last node and insert at the beginning
    list->next[temp] = -1;
    list->next[lastNode] = list->head;
    list->head = lastNode;
}

void delete_alternate_nodes(NodePool *list)
{
    if (list->head == -1 || list->next[list->head] == -1)
        return;

    int temp = list->head;
    while (temp != -1 && list->next[temp] != -1)
    {
        int toDelete = list->next[temp];
        list->next[temp] = list->next[toDelete];
        list->next[toDelete] = list->free;
        list->free = toDelete;
        temp = list->next[temp];
    }
}

void rotate_list(NodePool *list, int n)
{
    if (list->head == -1 || n <= 0)
        return;

    int size = find_size(list);
    if (n >= size)
        return;

    int temp = list->head;
    for (int i = 1; i < size - n; i++)
    {
        temp = list->next[temp];
    }

    int newHead = list->next[temp];
    list->next[temp] = -1;

    int last = newHead;
    while (list->next[last] != -1)
    {
        last = list->next[last];
    }

    list->next[last] = list->head;
    list->head = newHead;
}

void reverse_list(NodePool *list)
{
    if (list->head == -1)
        return;

    int prev = -1;
    int current = list->head;
    int nextNode;

    while (current != -1)
    {
        nextNode = list->next[current];
        list->next[current] = prev;
        prev = current;
        current = nextNode;
    }

    list->head = prev;
}

void sort_list(NodePool *list)
{
    if (list->head == -1)
        return;

    int temp1 = list->head;
    while (temp1 != -1)
    {
        int temp2 = list->next[temp1];
        while (temp2 != -1)
        {
            if (list->data[temp1] > list->data[temp2])
            {
                // Swap values
                int tempVal = list->data[temp1];
                list->data[temp1] = list->data[temp2];
                list->data[temp2] = tempVal;
            }
            temp2 = list->next[temp2];
        }
        temp1 = list->next[temp1];
    }
}

void build_reverse_list(NodePool *list, int arr[], int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        insert_front(list, arr[i]);
    }
}