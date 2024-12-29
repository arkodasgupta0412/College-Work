#include <stdio.h>
#include "p2a_q.c"

int main()
{
    Queue *q = NULL;
    int running = 1;

    while (running)
    {
        int choice;
        printf("\nMenu:\n");
        printf("1. Create Queue\n");
        printf("2. Enqueue (Push)\n");
        printf("3. Dequeue (Pop)\n");
        printf("4. Check Empty\n");
        printf("5. Check Full\n");
        printf("6. Current Size\n");
        printf("7. Capacity\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (q != NULL)
            {
                printf("Queue already exists. Dispose it first to create a new queue.\n");
                break;
            }
            int s;
            printf("Enter the capacity of the queue: ");
            scanf("%d", &s);
            q = create(s);
            printf("Queue created with capacity %d.\n", s);
            break;

        case 2:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            int elem;
            printf("Enter element to enqueue: ");
            scanf("%d", &elem);
            if (enqueue(q, elem))
                printf("Element %d enqueued.\n", elem);
            else
                printf("Queue is full. Cannot enqueue.\n");
            break;

        case 3:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            int dequeued_elem;
            dequeued_elem = dequeue(q);
            if (dequeued_elem != -1)
                printf("Element dequeued: %d\n", dequeued_elem);
            else
                printf("Queue is empty. Cannot dequeue.\n");
            break;

        case 4:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            if (is_empty(q))
                printf("Queue is empty.\n");
            else
                printf("Queue is not empty.\n");
            break;

        case 5:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            if (is_full(q))
                printf("Queue is full.\n");
            else
                printf("Queue is not full.\n");
            break;

        case 6:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            printf("Current size of the queue: %d\n", size(q));
            break;

        case 7:
            if (q == NULL)
            {
                printf("Queue not created yet. Use option 1 to create the queue first.\n");
                break;
            }
            printf("Capacity of the queue: %d\n", capacity(q));
            break;

        case 8:
            if (q != NULL)
            {
                dispose(q);
                q = NULL;
            }
            printf("Exiting program.\n");
            running = 0;
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
