/*
2.10. Implement the following functions in a menu-driven C program using the data structure operation of
Singly Linked List in the header file developed in problem 2.8:
a) print a list (i) in the same order, (ii) in the reverse order.
b) find the size of a list in number of nodes
c) check whether two lists are equal
d) search for a key in (i) an unordered list, (ii) an ordered list (Return the node if key is found and delete
the node from original list)
e) append a list at the end of another list.
f) delete the nth node, last node and first node of a list.
g) check whether a list is ordered
h) merge two sorted lists
i) insert a target node in the beginning, before a specified node and at the end of the list (sorted and
unsorted).
j) remove duplicates from a linked list (sorted and unsorted)
k) swap elements of a list pairwise
l) move last element to front of a list
m) delete alternate nodes of a list
n) rotate a list
o) delete a list.
p) reverse a list.
q) sort a list. 
*/


#include "p8.c"
#include <stdio.h>
#include <stdbool.h>
#include "p6.c"
#include "utils.c"
#include <limits.h>

// Function prototypes for additional operations
Node *createLL(int);
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
    printf("19. Build Reverse List\n");
    printf("20. Exit\n");
}

int main()
{
    int choice, data, key, position, size, op, n;
    Node *list1, *list2, *appendList, *mergedList, *reversed;

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
            list1 = createLL(size);
            break;

        case 2:
            printf("List: ");
            print(list1);
            break;

        case 3:
            printf("List in Reverse: ");
            print_reverse(list1);
            printf("NULL\n");
            break;

        case 4:
            printf("Size of List: %d\n", size_of_list(list1));
            break;

        case 5:
            printf("Enter size of another linked list: ");
            scanf("%d", &size);
            list2 = createLL(size);
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
            appendList = createLL(size);
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
            list2 = createLL(size);
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
            reversed = build_reverse_list(list1);
            printf("Original List: ");
            print(list1);
            printf("Built Reverse List: ");
            print(reversed);
            break;

        case 20:
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

Node *createLL(int size)
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
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function definitions
void print_reverse(Node *head)
{
    if (head == NULL)
        return;
    print_reverse(head->next);
    printf("%d->", head->data);
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

    Node *prev = NULL;
    Node *cur = *head;
    int tmp = INT_MAX;

    while (cur != NULL)
    {
        if (cur->data == key)
        {
            tmp = cur->data;
            if (prev == NULL)
            {
                *head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            free(cur);
            break;
        }

        if (cur->data > key)
            break;

        prev = cur;
        cur = cur->next;
    }

    return tmp;
}

void append_list(Node **head1, Node *head2)
{
    Node *cur = *head1;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = head2;
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

void insert_target_node(Node **head, int target, int before)
{
    Node *target_node = createNode(target);
    if (*head == NULL || (*head)->data == before)
    {
        insert_front(target_node, head);
        return;
    }
    Node *current = *head;
    while (current->next != NULL && current->next->data != before)
    {
        current = current->next;
    }
    if (current->next == NULL)
    {
        printf("Node with value %d not found.\n", before);
    }
    else
    {
        insert_after(target_node, &current);
    }
}

void remove_duplicates(Node **head)
{
    if (*head == NULL)
        return;
    Node *current = *head;
    while (current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}

void swap_pairwise(Node **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;
    Node *prev = NULL, *current = *head;
    while (current != NULL && current->next != NULL)
    {
        Node *next = current->next;
        current->next = next->next;
        next->next = current;
        if (prev == NULL)
        {
            *head = next;
        }
        else
        {
            prev->next = next;
        }
        prev = current;
        current = current->next;
    }
}

void move_last_to_front(Node **head)
{
    Node *cur = *head, *prev = NULL;
    while (cur->next != NULL)
    {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;
    insert_front(cur, head);
}

void delete_alternate_nodes(Node **head)
{
    if (*head == NULL)
        return;
    Node *current = *head;
    while (current != NULL && current->next != NULL)
    {
        Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        current = current->next;
    }
}

/* rotate list, shifts by n nodes */
void rotate_list(Node **head, int n)
{
    for (int i = 0; i < n; i++)
    {
        move_last_to_front(head);
    }
}

/* reverses the list in place */
void reverse_list(Node **head)
{
    Node *prev = NULL, *cur = *head, *nxt = (*head)->next;
    while (nxt != NULL)
    {
        cur->next = prev;
        prev = cur;
        cur = nxt;
        nxt = nxt->next;
    }
    cur->next = prev;
    (*head) = cur;
}

void sort_list(Node **head, int op)
{
    if (!head || !(*head)->next)
        return;

    Node *end = NULL; // Marks the end of the unsorted portion of the list

    while (end != (*head)->next)
    { // Continue until only one element is left unsorted
        Node *cur1 = *head;
        Node *cur2 = (*head)->next;

        while (cur2 != end)
        { // Iterate until reaching the unsorted end
            if (op == 0)
            {
                if (cur1->data > cur2->data)
                {
                    swap(&cur1->data, &cur2->data);
                }
                cur1 = cur2;
                cur2 = cur2->next;
            }
            else
            {
                if (cur1->data < cur2->data)
                {
                    swap(&cur1->data, &cur2->data);
                }
                cur1 = cur2;
                cur2 = cur2->next;
            }
        }
        end = cur1;
    }
}

Node *build_reverse_list(Node *head)
{
    Node *reversedList = NULL;

    Node *cur = head;
    while (cur != NULL)
    {
        Node *newNode = createNode(cur->data);
        insert_front(newNode, &reversedList);
        cur = cur->next;
    }

    return reversedList;
}
