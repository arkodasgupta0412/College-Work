#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *createBSTNode(int data)
{
    BSTNode *root = (BSTNode *)malloc(sizeof(BSTNode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;

    return root;
}

BSTNode *search(BSTNode *root, int data)
{
    /*-------------- SEARCHING ----------------------*/
    if (!root)
    {
        return NULL;
    }

    BSTNode *curr = root;
    while (curr != NULL && curr->data != data)
    {
        if (data < curr->data)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return (curr != NULL) ? curr : NULL;
}

void insert(BSTNode **root, int data)
{
    /*-------------- INSERTION ----------------------*/
    BSTNode *newNode = createBSTNode(data);
    if (*root == NULL) // If the tree is empty
    {
        *root = newNode;
        return;
    }

    BSTNode *curr = *root;
    BSTNode *prev = NULL;

    // Traverse the tree to find the correct position
    while (curr != NULL)
    {
        prev = curr;
        if (data < curr->data)
        {
            curr = curr->left;
        }
        else if (data > curr->data)
        {
            curr = curr->right;
        }
        else
        {
            // Value already exists in the BST; no duplicates allowed
            printf("Value %d already exists in the BST. Skipping insertion.\n", data);
            free(newNode); // Avoid memory leak
            return;
        }
    }

    // Insert the new node at the correct position
    if (data < prev->data)
    {
        prev->left = newNode;
    }
    else
    {
        prev->right = newNode;
    }
}

BSTNode *inorderSuccessor(BSTNode *node)
{
    node = node->right;
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

BSTNode *inorderPredecessor(BSTNode *node)
{
    node = node->left;
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

void deleteNode(BSTNode **root, int data)
{
    if (*root == NULL)
    {
        printf("Node not found\n");
        return;
    }

    if (data < (*root)->data)
    {
        deleteNode(&((*root)->left), data);
    }
    else if (data > (*root)->data)
    {
        deleteNode(&((*root)->right), data);
    }
    else
    {
        // Node to be deleted found

        // If the node is a leaf node
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            free(*root);
            *root = NULL;
        }
        // If the node has only the right child
        else if ((*root)->left == NULL)
        {
            BSTNode *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        // If the node has only the left child
        else if ((*root)->right == NULL)
        {
            BSTNode *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            // Node has two children
            BSTNode *pred = inorderPredecessor(*root);
            (*root)->data = pred->data;
            deleteNode(&((*root)->left), pred->data);
        }
    }
}

int findMax(BSTNode *root)
{
    // deepest rightmost node, i.e rightmost node with no right child
    BSTNode *curr = root;
    if (!root)
    {
        return -1;
    }

    while (curr->right != NULL)
    {
        curr = curr->right;
    }

    return curr->data;
}

int findMin(BSTNode *root)
{
    // deepest leftmost node, i.e leftmost node with no left child
    BSTNode *curr = root;
    if (!root)
    {
        return -1;
    }

    while (curr->left != NULL)
    {
        curr = curr->left;
    }

    return curr->data;
}

// Traversals
void visit(BSTNode *node)
{
    printf("%d ", node->data);
}

void inorder(BSTNode *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    visit(root);
    inorder(root->right);
}

void preorder(BSTNode *root)
{
    if (root == NULL)
        return;

    visit(root);
    preorder(root->left);
    preorder(root->right);
}

void postorder(BSTNode *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    visit(root);
}
