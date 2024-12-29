#include <stdio.h>
#include "TBT_traversals.c"

int main()
{
    TBTNode *root = NULL; // Initialize an empty threaded binary tree
    int choice, data;

    while (1)
    {
        printf("\n--- Threaded Binary Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Delete Node\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the value to insert: ");
            scanf("%d", &data);
            insert(&root, data); // Pass the root pointer by reference
            break;

        case 2:
            printf("Inorder Traversal: ");
            if (root == NULL)
                printf("Tree is empty.");
            else
                inorder(root);
            printf("\n");
            break;

        case 3:
            printf("Preorder Traversal: ");
            if (root == NULL)
                printf("Tree is empty.");
            else
                preorder(root);
            printf("\n");
            break;

        case 4:
            printf("Postorder Traversal: ");
            if (root == NULL)
                printf("Tree is empty.");
            else
                postorder(root);

            printf("\n");
            break;

        case 5:
            printf("Enter the value to delete: ");
            scanf("%d", &data);
            delete_node(&root, data); // Pass the root pointer by reference
            break;

        case 6:
            printf("Exiting program.\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
