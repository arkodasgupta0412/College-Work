#include <stdio.h>
#include "p2b_q.c"

int main()
{
    Queue *q = create();
    int choice, data;

    do
    {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue (Push)\n");
        printf("2. Dequeue (Pop)\n");
        printf("3. Check if Empty\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to enqueue: ");
            scanf("%d", &data);
            push(q, data);
            printf("Enqueued %d into the queue.\n", data);
            break;

        case 2:
            data = pop(q);
            if (data != -1)
                printf("Dequeued %d from the queue.\n", data);
            else
                printf("Queue is empty! Cannot dequeue.\n");
            break;

        case 3:
            if (is_empty(q))
                printf("Queue is empty.\n");
            else
                printf("Queue is not empty.\n");
            break;

        case 4:
            printf("Exiting...\n");
            dispose(q);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
