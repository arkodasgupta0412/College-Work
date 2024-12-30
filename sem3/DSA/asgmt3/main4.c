#include <stdio.h>
#include "TBT_traversals.c"

// Menu-driven interface
int main()
{
    struct TreeNode *root;
    init_t(&root);

    int choice, value;

    while (1)
    {
        printf("\nThreaded Binary Tree Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. In-order Traversal\n");
        printf("4. Pre-order Traversal\n");
        printf("5. Post-order Traversal\n");
        printf("6. Check if Tree is Empty\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insertNode(root, value);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;
        case 3:
            printf("In-order Traversal: ");
            inOrderTraversal(root);
            printf("\n");
            break;
        case 4:
            printf("Pre-order Traversal: ");
            preOrderTraversal(root);
            printf("\n");
            break;
        case 5:
            printf("Post-order Traversal: ");
            postOrderTraversal(root);
            printf("\n");
            break;
        case 6:
            printf("Tree is %s\n", empty_t(root) ? "empty" : "not empty");
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}