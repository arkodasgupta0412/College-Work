#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX

/* Threaded Binary Tree Node */
typedef struct TBTNode
{
    int data;
    int left_thread;       // 1 if left is a thread, 0 if it's a pointer to left child
    int right_thread;      // 1 if right is a thread, 0 if it's a pointer to right child
    struct TBTNode *left;  // Pointer to left child or inorder predecessor
    struct TBTNode *right; // Pointer to right child or inorder successor
} TBTNode;

/* Function to create a new node */
TBTNode *create_node(int data)
{
    TBTNode *node = (TBTNode *)malloc(sizeof(TBTNode));
    if (!node)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left_thread = 1;
    node->right_thread = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Function to find the inorder successor */
TBTNode *inorder_successor(TBTNode *node)
{
    if (node == NULL || node->right_thread == 1)
        return node->right;

    node = node->right;
    while (node->left_thread == 0)
    {
        node = node->left;
    }
    return node;
}

/* Function to find the inorder predecessor */
TBTNode *inorder_predecessor(TBTNode *node)
{
    if (node == NULL || node->left_thread == 1)
        return node->left;

    node = node->left;
    while (node->right_thread == 0)
    {
        node = node->right;
    }
    return node;
}

/* Function to insert a new node into the tree */
void insert(TBTNode **root, int data)
{
    TBTNode *new_node = create_node(data);

    if (*root == NULL)
    {
        *root = new_node; // Update root when the tree is empty
        return;
    }

    TBTNode *curr = *root;
    TBTNode *parent = NULL;

    while (curr != NULL)
    {
        parent = curr;
        if (data < curr->data)
        {
            if (curr->left_thread == 0)
                curr = curr->left;
            else
                break;
        }
        else
        {
            if (curr->right_thread == 0)
                curr = curr->right;
            else
                break;
        }
    }

    if (data < parent->data)
    {
        new_node->left = parent->left;
        new_node->right = parent;
        parent->left_thread = 0;
        parent->left = new_node;
    }
    else
    {
        new_node->right = parent->right;
        new_node->left = parent;
        parent->right_thread = 0;
        parent->right = new_node;
    }
}

void delete_node(TBTNode **root, int data)
{
    TBTNode *curr = *root, *parent = NULL;

    // Search for the node to delete
    while (curr != NULL)
    {
        if (data == curr->data)
            break;

        parent = curr;
        if (data < curr->data)
        {
            if (curr->left_thread == 0)
                curr = curr->left;
            else
                curr = NULL;
        }
        else
        {
            if (curr->right_thread == 0)
                curr = curr->right;
            else
                curr = NULL;
        }
    }

    if (curr == NULL)
    {
        printf("Node with value %d not found.\n", data);
        return;
    }

    // Node to delete is found
    if (curr->left_thread == 1 && curr->right_thread == 1)
    {
        // Case 1: Node with no children (leaf node)
        if (parent == NULL)
        {
            // Deleting root node
            *root = NULL;
        }
        else if (curr == parent->left)
        {
            parent->left_thread = 1;
            parent->left = curr->left; // Update predecessor link
        }
        else
        {
            parent->right_thread = 1;
            parent->right = curr->right; // Update successor link
        }
        free(curr);
    }
    else if (curr->left_thread == 0 || curr->right_thread == 0)
    {
        // Case 2: Node with one child
        TBTNode *child = (curr->left_thread == 0) ? curr->left : curr->right;

        if (parent == NULL)
        {
            // Deleting root node
            *root = child;
        }
        else if (curr == parent->left)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
        free(curr);
    }
    else
    {
        // Case 3: Node with two children
        TBTNode *successor = curr->right;
        while (successor->left_thread == 0)
            successor = successor->left;

        int successor_data = successor->data;
        delete_node(root, successor_data); // Delete successor node
        curr->data = successor_data;       // Copy successor's data into current node
    }
}
