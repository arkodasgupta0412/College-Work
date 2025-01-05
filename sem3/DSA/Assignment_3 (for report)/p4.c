/*
3.4 Define an ADT for a threaded Binary Tree.
Implement the ADT including the three traversals.
*/


#include <stdio.h>
#include <stdlib.h>

// Define the structure for a threaded binary tree node
struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    int rightThread; // 1 if the right pointer is a thread
};

// Function to initialize the tree
void init_t(struct TreeNode **root)
{
    *root = NULL;
}

// Function to check if the tree is empty
int empty_t(struct TreeNode *root)
{
    return root == NULL;
}

// Function to create a new node
struct TreeNode *createNode(int data)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rightThread = 0;
    return newNode;
}

// Function to find the inorder successor of a given node
struct TreeNode *findSuccessor(struct TreeNode *node)
{
    if (node == NULL || node->rightThread)
        return node->right;

    struct TreeNode *current = node->right;
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function to insert a node into the threaded binary tree
struct TreeNode *insertNode(struct TreeNode *root, int data)
{
    struct TreeNode *newNode = createNode(data);

    if (root == NULL)
        return newNode;

    struct TreeNode *current = root;
    struct TreeNode *parent = NULL;

    // Find the correct position for the new node
    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            if (current->left == NULL)
                break;
            current = current->left;
        }
        else
        {
            if (current->rightThread)
                break;
            current = current->right;
        }
    }

    // Insert the new node
    if (data < parent->data)
    {
        parent->left = newNode;
        newNode->right = parent;
        newNode->rightThread = 1;
    }
    else
    {
        if (parent->rightThread)
        {
            newNode->right = parent->right;
            newNode->rightThread = 1;
            parent->rightThread = 0;
        }
        parent->right = newNode;
    }

    return root;
}

// Function to delete a node with a specific key from the tree
struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
    if (root == NULL)
        return root;

    struct TreeNode *parent = NULL;
    struct TreeNode *current = root;

    // Locate the node to delete
    while (current != NULL && current->data != key)
    {
        parent = current;
        if (key < current->data)
            current = current->left;
        else
        {
            if (current->rightThread)
                break;
            current = current->right;
        }
    }

    if (current == NULL || current->data != key)
    {
        printf("Key %d not found in the tree.\n", key);
        return root;
    }

    // Node with only one child or no child
    if (current->left == NULL || current->rightThread)
    {
        struct TreeNode *child = current->left ? current->left : current->right;
        if (parent == NULL)
        {
            // Deleting the root node
            free(current);
            return child;
        }
        if (current == parent->left)
            parent->left = child;
        else
        {
            if (current->rightThread)
                parent->rightThread = 1;
            parent->right = child;
        }
        free(current);
    }
    else
    {
        // Node with two children: Get the inorder successor
        struct TreeNode *successor = current->right;
        struct TreeNode *successorParent = current;
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // Replace current's data with successor's data
        current->data = successor->data;

        // Delete the inorder successor
        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
        {
            if (successor->rightThread)
                successorParent->rightThread = 1;
            successorParent->right = successor->right;
        }
        free(successor);
    }
    return root;
}
