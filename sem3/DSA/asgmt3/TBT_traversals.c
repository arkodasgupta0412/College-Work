#include <stdio.h>
#include "p4.c"

/* Inorder traversal of a threaded binary tree */
void inorder(TBTNode *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    TBTNode *curr = root;
    while (curr->left_thread == 0)
        curr = curr->left;

    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = inorder_successor(curr);
    }
    printf("\n");
}

/* Preorder traversal of a threaded binary tree */
void preorder(TBTNode *root)
{
    TBTNode *curr = root;
    while (curr != NULL)
    {
        // Print the current node's data
        printf("%d ", curr->data);

        // If left_thread is 0, move to the left child
        if (curr->left_thread == 0)
        {
            curr = curr->left;
        }
        else
        {
            // If left_thread is 1, move to the right child, but avoid going into infinite loops
            if (curr->right_thread == 0)
            {
                curr = curr->right;
            }
            else
            {
                break; // Both threads are 1, stop traversal
            }
        }
    }
}

/* Postorder traversal of a threaded binary tree */
void postorder(TBTNode *root)
{
    TBTNode *curr = root;
    while (curr != NULL)
    {
        // Move to the leftmost node first
        while (curr->left_thread == 0) // Keep moving left until reaching a leaf node
        {
            curr = curr->left;
        }

        // Now perform the postorder traversal by using the thread-based traversal
        while (curr != NULL)
        {
            // Print the current node's data after the left and right children have been visited
            printf("%d ", curr->data);

            // Move to the in-order predecessor node
            if (curr->right_thread == 1) // If right thread exists, it points to the successor node
            {
                curr = curr->right;
            }
            else // If no right thread, use the in-order predecessor
            {
                curr = inorder_predecessor(curr); // Custom function to find the predecessor
            }
        }
    }
}