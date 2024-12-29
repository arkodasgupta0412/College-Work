#include <stdio.h>
#include "p5.c"

int main()
{
    BSTNode *root = NULL;
    int choice, data;

    do
    {
        printf("\nBinary Search Tree Menu:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Search for a node\n");
        printf("4. Find maximum value\n");
        printf("5. Find minimum value\n");
        printf("6. Inorder traversal\n");
        printf("7. Preorder traversal\n");
        printf("8. Postorder traversal\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            if (root == NULL)
            {
                root = createBSTNode(data);
            }
            else
            {
                insert(&root, data); // Pass-by-address for insertion
            }
            printf("Inserted %d into the BST.\n", data);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &data);
            deleteNode(&root, data); // Pass-by-address for deletion
            printf("Deleted %d from the BST (if it existed).\n", data);
            break;

        case 3:
            printf("Enter value to search for: ");
            scanf("%d", &data);
            BSTNode *result = search(root, data);
            if (result)
            {
                printf("Value %d found in the BST.\n", result->data);
            }
            else
            {
                printf("Value %d not found in the BST.\n", data);
            }
            break;

        case 4:
            data = findMax(root);
            if (data != -1)
            {
                printf("Maximum value in the BST: %d\n", data);
            }
            else
            {
                printf("The BST is empty.\n");
            }
            break;

        case 5:
            data = findMin(root);
            if (data != -1)
            {
                printf("Minimum value in the BST: %d\n", data);
            }
            else
            {
                printf("The BST is empty.\n");
            }
            break;

        case 6:
            printf("Inorder traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 7:
            printf("Preorder traversal: ");
            preorder(root);
            printf("\n");
            break;

        case 8:
            printf("Postorder traversal: ");
            postorder(root);
            printf("\n");
            break;

        case 9:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}
