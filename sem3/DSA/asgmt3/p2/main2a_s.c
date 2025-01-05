#include <stdio.h>
#include "p2a_s.c"

int main()
{
    Stack *s;
    int running = 1;
    while (running)
    {
        int ch;
        printf("\nEnter choice:\n1. Create\n2. Push\n3. Pop\n4. Check Empty\n5. Check Full\n6. Size\n7. Capacity\n8. Exit\n");
        scanf("%d", &ch);

        switch (ch)
        {

        case 1:
        {
            int size;
            printf("Enter size of stack: ");
            scanf("%d", &size);
            s = create(size);
            break;
        }

        case 2:
        {
            int e;
            printf("Enter element to push: ");
            scanf("%d", &e);
            if (push(s, e))
            {
                printf("Element pushed\n");
            }
            else
            {
                printf("Overflow. Stack size full\n");
            }
            break;
        }

        case 3:
        {
            int x = pop(s);
            if (x == -1)
            {
                printf("Underflow. Stack is empty\n");
            }
            else
            {
                printf("Element popped: %d\n", x);
            }
            break;
        }

        case 4:
        {
            if (is_empty(s))
            {
                printf("Stack is empty\n");
            }
            else
            {
                printf("stack not empty\n");
            }
            break;
        }

        case 5:
        {
            if (is_full(s))
            {
                printf("Stack is full\n");
            }
            else
            {
                printf("Stack not full\n");
            }
            break;
        }

        case 6:
        {
            printf("Size of stack: %d\n", size(s));
            break;
        }

        case 7:
        {
            printf("Max capacity of stack: %d\n", capacity(s));
            break;
        }

        case 8:
        {
            running = 0;
            dispose(s);
            break;
        }

        default:
            printf("Invalid choice. Enter again\n");
            break;
        }
    }

    return 0;
}