/*
2.12. Repeat problems 2.8 and 2.10 for a circular single linked list, doubly linked list and circular doubly
linked list. You need to develop Build_list and Build_list_reverse, as well as Print_list for each case. 
*/


#include "csll.c"
#include <stdio.h>
#include <stdbool.h>
#include "../p6.c"
#include "../utils.c"
#include <limits.h>

Node *createCSLL(int);
void print(Node *head);
void print_reverse(Node *head, Node *current, int *cnt, int size);
int size_of_list(Node *head);
bool are_lists_equal(Node *head1, Node *head2);
int search_key(Node **head, int key);
void append_list(Node **head1, Node *head2);
void delete_nth_node(Node **head, int n);
bool is_ordered(Node *head);
Node *merge_sorted_lists(Node *head1, Node *head2);
void insert_target_node(Node **head, int target, int before);
void remove_duplicates(Node **head);
void swap_pairwise(Node **head);
void move_last_to_front(Node **head);
void delete_alternate_nodes(Node **head);
void rotate_list(Node **head, int n);
void reverse_list(Node **head);
void sort_list(Node **head, int op);
Node *build_reverse_list(Node *head);

void menu()
{
    printf("\nMenu:\n");
    printf("1. Create Linked List\n");
    printf("2. Print List\n");
    printf("3. Print List in Reverse\n");
    printf("4. Find Size of List\n");
    printf("5. Check if Two Lists are Equal\n");
    printf("6. Search and delete the Key\n");
    printf("7. Append List\n");
    printf("8. Delete Nth Node\n");
    printf("9. Check if List is Ordered\n");
    printf("10. Merge Two Sorted Lists\n");
    printf("11. Insert Target Node\n");
    printf("12. Remove Duplicates\n");
    printf("13. Swap Elements Pairwise\n");
    printf("14. Move Last Element to Front\n");
    printf("15. Delete Alternate Nodes\n");
    printf("16. Rotate List\n");
    printf("17. Reverse List\n");
    printf("18. Sort List\n");
    printf("19. Exit\n");
}

int main()
{
    int choice, data, key, position, size, op, n;
    Node *list1, *list2, *appendList, *mergedList;

    menu();

    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter size of LinkedList: ");
            scanf("%d", &size);
            list1 = createCSLL(size);
            break;

        case 2:
            printf("List: ");
            print(list1);
            break;

        case 3:
            printf("List in Reverse: ");
            int cnt = 0;
            print_reverse(list1, list1, &cnt, size_of_list(list1));
            printf("HEAD\n");
            break;

        case 4:
            printf("Size of List: %d\n", size_of_list(list1));
            break;

        case 5:
            printf("Enter size of another linked list: ");
            scanf("%d", &size);
            list2 = createCSLL(size);
            print(list2);
            printf("Lists are %s\n", are_lists_equal(list1, list2) ? "Equal" : "Not Equal");
            break;

        case 6:
            printf("Enter key to search: ");
            scanf("%d", &key);
            int foundNodeData = search_key(&list1, key);
            if (foundNodeData != INT_MAX)
            {
                printf("Key found and deleted: %d\n", foundNodeData);
            }
            else
            {
                printf("Key not found.\n");
            }
            break;

        case 7:
            printf("Enter size of another linked list: ");
            scanf("%d", &size);
            appendList = createCSLL(size);
            print(appendList);
            append_list(&list1, appendList);
            break;

        case 8:
            printf("Enter position to delete (1-based index): ");
            scanf("%d", &position);
            delete_nth_node(&list1, position);
            break;

        case 9:
            printf("List is %sordered.\n", is_ordered(list1) ? "" : "not ");
            break;

        case 10:
            printf("Enter size of another linked list: ");
            scanf("%d", &size);
            list2 = createCSLL(size);
            print(list1);
            print(list2);
            mergedList = merge_sorted_lists(list1, list2);
            printf("Merged Sorted List: ");
            print(mergedList);
            break;

        case 11:
            printf("Enter target value to insert: ");
            scanf("%d", &data);
            printf("Enter node value to insert before: ");
            scanf("%d", &key);
            insert_target_node(&list1, data, key);
            break;

        case 12:
            remove_duplicates(&list1);
            break;

        case 13:
            swap_pairwise(&list1);
            break;

        case 14:
            move_last_to_front(&list1);
            break;

        case 15:
            delete_alternate_nodes(&list1);
            break;

        case 16:
            printf("Enter shift: ");
            scanf("%d", &n);
            rotate_list(&list1, n);
            break;

        case 17:
            reverse_list(&list1);
            printf("list reversed\n");
            break;

        case 18:
            printf("Enter comparator (0 for inc, 1 for dec): ");
            scanf("%d", &op);
            sort_list(&list1, op);
            printf("list sorted\n");
            break;

        case 19:
            printf("Exiting...\n");
            exit(0);
            break;

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

    Node *l = build_reverse_list(list1);
    print(l);

    return 0;
}

Node *createCSLL(int size)
{
    Node *head = init_l();
    insert_front(createNode(0), &head);
    Node *cur = head;
    int data;

    for (int i = 0; i < size; i++)
    {
        printf("Enter node %d: ", i + 1);
        scanf("%d", &data);
        insert_after(createNode(data), &cur);
        cur = cur->next;
    }

    cur->next = head->next;
    Node *temp = head;
    head = head->next;
    free(temp);

    return head;
}

void print(Node *head)
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

void print_reverse(Node *head, Node *current, int *cnt, int size)
{
    if (*cnt == size)
        return;
    (*cnt)++;
    print_reverse(head, current->next, cnt, size);
    printf("%d->", current->data);
}

int size_of_list(Node *head)
{
    if (head == NULL)
        return 0;

    int count = 1;
    Node *temp = head->next;
    while (temp != head)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

bool are_lists_equal(Node *head1, Node *head2)
{
    if (head1 == NULL && head2 == NULL)
        return 1;
    if (head1 == NULL || head2 == NULL)
        return 0;

    Node *temp1 = head1;
    Node *temp2 = head2;
    do
    {
        if (temp1->data != temp2->data)
            return 0;

        temp1 = temp1->next;
        temp2 = temp2->next;
    } while (temp1 != head1 && temp2 != head2);

    return (temp1 == head1 && temp2 == head2);
}

int search_key(Node **head, int key)
{
    if (*head == NULL)
        return INT_MAX;

    Node *prev = NULL;
    Node *cur = *head;
    int tmp = INT_MAX;

    do
    {
        if (cur->data == key)
        {
            tmp = cur->data;

            if (*head == cur)
            {
                *head = cur->next;
            }

            else
            {
                prev->next = cur->next;
            }

            free(cur);
            return tmp;
        }

        prev = cur;
        cur = cur->next;

    } while (cur != *head);

    return INT_MAX;
}

void append_list(Node **head1, Node *head2)
{
    if (*head1 == NULL)
    {
        *head1 = head2;
        return;
    }

    Node *temp = *head1;
    while (temp->next != *head1)
    {
        temp = temp->next;
    }
    temp->next = head2;
    Node *temp2 = head2;
    while (temp2->next != head2)
    {
        temp2 = temp2->next;
    }
    temp2->next = *head1;
}

void delete_nth_node(Node **head, int n)
{
    int i = 1;
    if (n > size_of_list(*head))
    {
        printf("n exceeds size of list\n");
        return;
    }

    if (n == 1)
    {
        delete_front(head);
        return;
    }

    Node *cur = *head;
    while (i < n - 1)
    {
        cur = cur->next;
        i++;
    }
    delete_after(&cur);
}

bool is_ordered(Node *head)
{
    int size = size_of_list(head);
    Node *cur = head;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = cur->data;
        cur = cur->next;
    }

    return checkSorted(arr, size);
}

Node *merge_sorted_lists(Node *head1, Node *head2)
{
    Node *list3 = init_l();

    if (!is_ordered(head1) && !is_ordered(head2))
    {
        printf("The lists are not sorted\n");
        return list3;
    }

    insert_front(createNode(0), &list3);
    Node *cur1 = head1, *cur2 = head2, *cur3 = list3;

    while (cur1 != NULL && cur2 != NULL)
    {
        if (cur1->data <= cur2->data)
        {
            insert_after(createNode(cur1->data), &cur3);
            cur1 = cur1->next;
            cur3 = cur3->next;
        }
        else
        {
            insert_after(createNode(cur2->data), &cur3);
            cur2 = cur2->next;
            cur3 = cur3->next;
        }
    }

    while (cur1 != NULL)
    {
        insert_after(createNode(cur1->data), &cur3);
        cur1 = cur1->next;
        cur3 = cur3->next;
    }

    while (cur2 != NULL)
    {
        insert_after(createNode(cur2->data), &cur3);
        cur2 = cur2->next;
        cur3 = cur3->next;
    }

    cur3->next = list3->next;

    return list3->next;
}

void insert_target_node(Node **head, int target, int before)
{
    Node *new_node = createNode(target);

    if (empty_l(*head))
    {
        *head = new_node;
        return;
    }

    if ((*head)->data == before)
    {
        insert_front(new_node, head);
        return;
    }

    Node *cur = *head;
    Node *prev = NULL;
    do
    {
        if (cur->data == before)
        {
            if (prev != NULL)
            {
                insert_after(new_node, &prev);
                return;
            }
        }
        prev = cur;
        cur = cur->next;
    } while (cur != *head);

    printf("Node with data %d not found in the list.\n", before);
    free(new_node);
}

void remove_duplicates(Node **head)
{
    if (*head == NULL)
        return;

    Node *cur = *head;
    while (cur != NULL && cur->next != *head)
    {
        Node *prev = cur;
        Node *temp = cur->next;
        while (temp != *head)
        {
            if (cur->data == temp->data)
            {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        cur = cur->next;
    }
}

void swap_pairwise(Node **head)
{
    if (*head == NULL || (*head)->next == *head)
        return;

    Node *temp = *head;
    do
    {
        swap(&temp->data, &temp->next->data);
        temp = temp->next->next;

    } while (temp != *head && temp->next != *head);
}

void move_last_to_front(Node **head)
{
    if (*head == NULL || (*head)->next == *head)
        return;

    Node *cur = *head, *prev = NULL;
    while (cur->next != *head)
    {
        prev = cur;
        cur = cur->next;
    }
    insert_front(createNode(cur->data), head);
    prev->next = *head;
    free(cur);
}

void delete_alternate_nodes(Node **head)
{
    if (*head == NULL || (*head)->next == *head)
        return;

    Node *cur = *head;
    do
    {
        delete_after(&cur);
        cur = cur->next;

    } while (cur != *head || cur->next != *head);
}

void rotate_list(Node **head, int n)
{
    for (int i = 0; i < n; i++)
    {
        move_last_to_front(head);
    }
}

void reverse_list(Node **head)
{
    if (*head == NULL)
        return;

    Node *prev = NULL;
    Node *current = *head;
    Node *next;
    do
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != (*head));

    (*head)->next = prev;
    *head = prev;
}

void sort_list(Node **head, int op)
{
    Node *current = *head, *index = NULL;
    int temp;

    if (*head == NULL)
    {
        printf("List is empty");
        return;
    }
    else
    {
        do
        {
            index = current->next;
            while (index != *head)
            {
                if (op == 0)
                {
                    if (current->data > index->data)
                    {
                        swap(&current->data, &index->data);
                    }
                    index = index->next;
                }
                else
                {
                    if (current->data < index->data)
                    {
                        swap(&current->data, &index->data);
                    }
                    index = index->next;
                }
            }
            current = current->next;
        } while (current->next != *head);
    }
}

Node *build_reverse_list(Node *head)
{
    if (empty_l(head))
    {
        printf("List is empty\n");
        return NULL;
    }

    Node *reversed_head = NULL, *current = head, *temp;
    do
    {
        Node *new_node = createNode(current->data);
        insert_front(new_node, &reversed_head);
        current = current->next;

        if (reversed_head->next == NULL)
        {
            temp = reversed_head;
        }

    } while (current != head);

    temp->next = reversed_head;

    return reversed_head;
}