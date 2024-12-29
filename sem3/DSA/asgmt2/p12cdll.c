#include "p8cdll.c"
#include <stdio.h>
#include <stdbool.h>
#include "p6.c"
#include "utils.c"
#include <limits.h>

// Function prototypes for additional operations
Node *createCDLL(int);
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

// Main function
int main()
{
    int choice, data, key, position, size, op;
    Node *list1, *list2, *appendList, *mergedList;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Create Linked List\n");
        printf("2. Print List\n");
        printf("3. Print List in Reverse\n");
        printf("4. Find Size of List\n");
        printf("5. Check if Two Lists are Equal\n");
        printf("6. Search for a Key\n");
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
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter size of LinkedList: ");
            scanf("%d", &size);
            list1 = createCDLL(size);
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
            list2 = createCDLL(size);
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
            appendList = createCDLL(size);
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
            list2 = createCDLL(size);
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
            break;
        }
    }

    return 0;
}

void print(Node *head)
{
    if (empty_l(head))
    {
        printf("List is empty\n");
        return;
    }
    Node *current = head;
    do
    {
        printf("%d <-> ", current->data);
        current = current->next;
    } while (current != head);
    printf("HEAD\n");
}

void print_reverse(Node *head)
{
    if (empty_l(head))
    {
        printf("List is empty\n");
        return;
    }
    Node *current = head->prev; // Start from the last node (prev of the head)
    do
    {
        printf("%d <-> ", current->data);
        current = current->prev; // Move towards the head
    } while (current != head->prev);
    printf("HEAD\n");
}

int size_of_list(Node *head)
{
    if (empty_l(head))
        return 0;
    int size = 1;
    Node *current = head->next;
    while (current != head)
    {
        size++;
        current = current->next;
    }
    return size;
}

bool are_lists_equal(Node *head1, Node *head2)
{
    if (empty_l(head1) && empty_l(head2))
        return true;
    if (empty_l(head1) || empty_l(head2))
        return false;

    Node *cur1 = head1, *cur2 = head2;
    do
    {
        if (cur1->data != cur2->data)
            return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    } while (cur1 != head1 && cur2 != head2);
    return cur1 == head1 && cur2 == head2;
}

int search_key(Node **head, int key)
{
    if (empty_l(*head))
        return -1;
    Node *current = *head;
    int index = 0;
    do
    {
        if (current->data == key)
            return index;
        current = current->next;
        index++;
    } while (current != *head);
    return -1;
}

void append_list(Node **head1, Node *head2)
{
    if (empty_l(*head1))
    {
        *head1 = head2;
    }
    else if (!empty_l(head2))
    {
        Node *tail1 = (*head1)->prev;
        Node *tail2 = head2->prev;

        tail1->next = head2;
        head2->prev = tail1;

        tail2->next = *head1;
        (*head1)->prev = tail2;
    }
}

void delete_nth_node(Node **head, int n)
{
    if (empty_l(*head))
        return;

    Node *current = *head;
    if (n == 0)
    {
        delete_front(head); // Special case for the first node
        return;
    }

    int i = 0;
    do
    {
        if (i == n)
        {
            Node *toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == *head)
                *head = current->next; // If we delete the head, update head
            free(toDelete);
            return;
        }
        i++;
        current = current->next;
    } while (current != *head);
}

bool is_ordered(Node *head)
{
    if (empty_l(head))
        return true;

    Node *current = head;
    do
    {
        if (current->next != head && current->data > current->next->data)
        {
            return false;
        }
        current = current->next;
    } while (current != head);
    return true;
}

Node *merge_sorted_lists(Node *head1, Node *head2)
{
    if (empty_l(head1))
        return head2;
    if (empty_l(head2))
        return head1;

    Node *mergedList = NULL;
    Node *cur1 = head1, *cur2 = head2;

    do
    {
        if (cur1->data <= cur2->data)
        {
            insert_front(createNode(cur1->data), &mergedList);
            cur1 = cur1->next;
        }
        else
        {
            insert_front(createNode(cur2->data), &mergedList);
            cur2 = cur2->next;
        }
    } while (cur1 != head1 || cur2 != head2);

    return mergedList;
}

void insert_target_node(Node **head, int target, int before)
{
    if (empty_l(*head))
        return;

    Node *current = *head;
    do
    {
        if (current->data == before)
        {
            Node *newNode = createNode(target);
            insert_after(newNode, &current->prev);
            return;
        }
        current = current->next;
    } while (current != *head);
}

void remove_duplicates(Node **head)
{
    if (empty_l(*head))
        return;

    Node *cur1 = *head, *cur2;
    do
    {
        cur2 = cur1->next;
        while (cur2 != *head)
        {
            if (cur1->data == cur2->data)
            {
                Node *toDelete = cur2;
                cur1->next = cur2->next;
                cur2->next->prev = cur1;
                free(toDelete);
                cur2 = cur1->next;
            }
            else
            {
                cur2 = cur2->next;
            }
        }
        cur1 = cur1->next;
    } while (cur1 != *head);
}

void swap_pairwise(Node **head)
{
    if (empty_l(*head))
        return;

    Node *current = *head;
    while (current != *head || current->next != *head)
    {
        Node *nextNode = current->next;
        if (nextNode != *head)
        {
            current->next = nextNode->next;
            nextNode->next->prev = current;

            nextNode->prev = current->prev;
            if (current == *head)
                *head = nextNode; // Update head if needed
            current->prev = nextNode;
            nextNode->next = current;
        }
        current = current->next->next;
    }
}

void move_last_to_front(Node **head)
{
    if (empty_l(*head) || (*head)->next == *head)
        return; // Only one node
    Node *last = (*head)->prev;
    Node *newHead = last;
    (*head)->prev = last;
    last->next = *head;
    newHead->prev = NULL;
    (*head) = newHead;
}

void delete_alternate_nodes(Node **head)
{
    if (empty_l(*head))
        return;

    Node *current = *head;
    while (current != *head && current->next != *head)
    {
        Node *toDelete = current->next;
        current->next = toDelete->next;
        toDelete->next->prev = current;
        free(toDelete);
        current = current->next;
    }
}

void rotate_list(Node **head)
{
    if (empty_l(*head) || (*head)->next == *head)
        return;

    Node *last = (*head)->prev;
    *head = (*head)->next;
    last->next = *head;
    (*head)->prev = last;
}

void reverse_list(Node **head)
{
    if (empty_l(*head) || (*head)->next == *head)
        return;

    Node *current = *head;
    Node *prevNode = NULL;
    Node *nextNode;

    do
    {
        nextNode = current->next;
        current->next = prevNode;
        current->prev = nextNode;
        prevNode = current;
        current = nextNode;
    } while (current != *head);

    *head = prevNode;
}

void sort_list(Node **head, int op)
{
    if (empty_l(*head))
        return;

    bool swapped;
    do
    {
        swapped = false;
        Node *current = *head;
        do
        {
            Node *nextNode = current->next;
            if ((op == 1 && current->data > nextNode->data) ||
                (op == 0 && current->data < nextNode->data))
            {

                // Swap data
                int temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;

                swapped = true;
            }
            current = nextNode;
        } while (current != *head && current->next != *head);
    } while (swapped);
}

Node *build_reverse_list(Node *head)
{
    Node *reversedList = NULL;

    if (head == NULL)
    {
        return NULL;
    }

    Node *cur = head;
    do
    {
        Node *newNode = createNode(cur->data);
        insert_end(&reversedList, newNode);
        cur = cur->next;
    } while (cur != head);

    return reversedList;
}
