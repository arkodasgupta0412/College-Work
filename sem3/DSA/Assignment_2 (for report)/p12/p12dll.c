#include "dll.c"
#include <stdio.h>
#include <stdbool.h>
#include "../p6.c"
#include "../utils.c"
#include <limits.h>

// Function prototypes for additional DLL operations
Node *createDLL(int);
void print(Node *head);
void print_reverse(Node *head);
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
void rotate_list(Node **head);
void reverse_list(Node **head);
void sort_list(Node **head, int op);
Node *build_reverse_list(Node *head);

void menu()
{
    printf("\nMenu:\n");
    printf("1. Create Doubly Linked List\n");
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
    int choice, data, key, position, size, op;
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
            list1 = createDLL(size);
            break;

        case 2:
            printf("List: ");
            print(list1);
            break;

        case 3:
            printf("List in Reverse: ");
            print_reverse(list1);
            break;

        case 4:
            printf("Size of List: %d\n", size_of_list(list1));
            break;

        case 5:
            printf("Enter size of another linked list: ");
            scanf("%d", &size);
            list2 = createDLL(size);
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
            appendList = createDLL(size);
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
            list2 = createDLL(size);
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
            rotate_list(&list1);
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

    return 0;
}

Node *createDLL(int size)
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

    delete_front(&head);
    return head;
}

void print(Node *head)
{
    printf("NULL <-> ");
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void print_reverse(Node *head)
{
    if (empty_l(head))
    {
        printf("List is empty\n");
        return;
    }

    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    printf("NULL <-> ");
    while (current != NULL)
    {
        printf("%d <-> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

int size_of_list(Node *head)
{
    Node *p = head;
    int size = 0;
    while (p != NULL)
    {
        size++;
        p = p->next;
    }
    return size;
}

bool are_lists_equal(Node *head1, Node *head2)
{
    if (size_of_list(head1) != size_of_list(head2))
    {
        return false;
    }

    Node *p1 = head1, *p2 = head2;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data != p2->data)
            return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

int search_key(Node **head, int key)
{
    if (*head == NULL)
        return INT_MAX;

    Node *cur = *head;
    while (cur != NULL)
    {
        if (cur->data == key)
        {
            int data = cur->data;
            if (cur->prev)
                cur->prev->next = cur->next;
            if (cur->next)
                cur->next->prev = cur->prev;
            if (cur == *head)
                *head = cur->next;
            free(cur);
            return data;
        }
        cur = cur->next;
    }
    return INT_MAX;
}

void append_list(Node **head1, Node *head2)
{
    Node *cur = *head1;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = head2;
    head2->prev = cur;
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
    // print(list3);
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

    return list3->next;
}

// Function to insert a node with target value before a given node
void insert_target_node(Node **head, int target, int before)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    Node *cur = *head;
    while (cur != NULL && cur->data != before)
    {
        cur = cur->next;
    }

    if (cur == NULL)
    {
        printf("Node with value %d not found.\n", before);
        return;
    }

    Node *new_node = createNode(target);
    new_node->prev = cur->prev;
    new_node->next = cur;
    if (cur->prev)
    {
        cur->prev->next = new_node;
    }
    else
    {
        *head = new_node;
    }
    cur->prev = new_node;
}

// Function to remove duplicate elements from a DLL
void remove_duplicates(Node **head)
{
    if (*head == NULL)
    {
        return;
    }

    Node *outer = *head;
    while (outer != NULL)
    {
        Node *inner = outer->next;
        while (inner != NULL)
        {
            if (inner->data == outer->data)
            {
                Node *duplicate = inner;
                inner = inner->next;
                if (duplicate->prev)
                {
                    duplicate->prev->next = duplicate->next;
                }
                if (duplicate->next)
                {
                    duplicate->next->prev = duplicate->prev;
                }
                free(duplicate);
            }
            else
            {
                inner = inner->next;
            }
        }
        outer = outer->next;
    }
}

// Function to swap elements pairwise
void swap_pairwise(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *cur = *head;
    while (cur != NULL && cur->next != NULL)
    {
        int temp = cur->data;
        cur->data = cur->next->data;
        cur->next->data = temp;
        cur = cur->next->next;
    }
}

// Function to move the last element to the front
void move_last_to_front(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    if (tail->prev)
    {
        tail->prev->next = NULL;
    }
    tail->prev = NULL;
    tail->next = *head;
    (*head)->prev = tail;
    *head = tail;
}

// Function to delete alternate nodes in a DLL
void delete_alternate_nodes(Node **head)
{
    if (*head == NULL)
    {
        return;
    }

    Node *cur = *head;
    while (cur != NULL && cur->next != NULL)
    {
        Node *temp = cur->next;
        cur->next = temp->next;
        if (temp->next)
        {
            temp->next->prev = cur;
        }
        free(temp);
        cur = cur->next;
    }
}

// Function to rotate a DLL by moving the head to the end
void rotate_list(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *cur = *head;
    *head = (*head)->next;
    (*head)->prev = NULL;

    while (cur->next != NULL)
    {
        cur = cur->next;
    }

    cur->next = *head;
    (*head)->prev = cur;
    cur->prev->next = NULL;
}

// Function to reverse a DLL
void reverse_list(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *cur = *head;
    Node *temp = NULL;

    while (cur != NULL)
    {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }

    if (temp != NULL)
    {
        *head = temp->prev;
    }
}

// Function to sort the DLL in ascending or descending order
void sort_list(Node **head, int op)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *i, *j;
    for (i = *head; i->next != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if ((op == 0 && i->data > j->data) || (op == 1 && i->data < j->data))
            {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

Node *build_reverse_list(Node *head)
{
    Node *reversedList = NULL;

    Node *cur = head;
    while (cur != NULL)
    {
        Node *newNode = createNode(cur->data);
        insert_front(reversedList, &newNode);
        cur = cur->next;
    }

    return reversedList;
}