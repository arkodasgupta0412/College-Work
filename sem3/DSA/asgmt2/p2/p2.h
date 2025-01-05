#ifndef P2_H
#define P2_H

// Node definition for a non-zero element in the sparse matrix
typedef struct Node
{
    int row;   // Row index of the element
    int col;   // Column index of the element
    int value; // Non-zero value
    struct Node *next;
} Node;

// Define a sparse matrix as a linked list of non-zero elements
typedef struct SparseMatrix
{
    int rows;   // Total number of rows in the matrix
    int cols;   // Total number of columns in the matrix
    Node *head; // Pointer to the head of the linked list
} SparseMatrix;

// Function declarations
SparseMatrix *createSparseMatrix(int rows, int cols);
void insertElement(SparseMatrix *mat, int row, int col, int value);
void displaySparseMatrix(const SparseMatrix *mat);
SparseMatrix *addSparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2);
SparseMatrix *subtractSparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2);
SparseMatrix *multiplySparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2);
void deleteSparseMatrix(SparseMatrix *mat);

#endif // P2_H
