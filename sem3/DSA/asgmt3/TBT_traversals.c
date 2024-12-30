#include <stdio.h>
#include "p4.c"

// Function for in-order traversal
void inOrderTraversal(struct TreeNode *root)
{
    struct TreeNode *current = root;
    while (current != NULL)
    {
        while (current->left != NULL)
            current = current->left;

        printf("%d ", current->data);

        while (current->rightThread)
        {
            current = current->right;
            printf("%d ", current->data);
        }

        current = current->right;
    }
}

// Function for pre-order traversal
void preOrderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preOrderTraversal(root->left);
    if (!root->rightThread)
        preOrderTraversal(root->right);
}

// Function for post-order traversal
void postOrderTraversal(struct TreeNode *root)
{
    if (root == NULL)
        return;

    postOrderTraversal(root->left);
    if (!root->rightThread)
        postOrderTraversal(root->right);
    printf("%d ", root->data);
}