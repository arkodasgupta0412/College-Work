#include <stdio.h>
#include "p2b_s.c"

int main()
{
    Stack *s = create();
    int choice, data;

    do
    {
        printf("\nStack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Check if Empty\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to push: ");
            scanf("%d", &data);
            push(s, data);
            printf("Pushed %d onto the stack.\n", data);
            break;

        case 2:
            data = pop(s);
            if (data != -1)
                printf("Popped %d from the stack.\n", data);
            break;

        case 3:
            if (is_empty(s))
                printf("Stack is empty.\n");
            else
                printf("Stack is not empty.\n");
            break;

        case 4:
            printf("Exiting...\n");
            dispose(s);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
