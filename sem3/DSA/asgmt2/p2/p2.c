#include <stdio.h>
#include <stdlib.h>
#include "p2.h"

// Create a new sparse matrix
SparseMatrix *createSparseMatrix(int rows, int cols)
{
    SparseMatrix *mat = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->head = NULL;
    return mat;
}

// Insert a non-zero element into the sparse matrix
void insertElement(SparseMatrix *mat, int row, int col, int value)
{
    if (row >= mat->rows || col >= mat->cols || row < 0 || col < 0)
    {
        printf("Invalid position!\n");
        return;
    }

    if (value == 0)
        return; // We don't store zero elements

    Node *current = mat->head;
    Node *prev = NULL;

    // Traverse to find the correct position
    while (current != NULL && (current->row < row || (current->row == row && current->col < col)))
    {
        prev = current;
        current = current->next;
    }

    // If the element already exists, update its value
    if (current != NULL && current->row == row && current->col == col)
    {
        if (value != 0)
        {
            current->value = value;
        }
        else
        {
            // If new value is zero, remove the node
            if (prev == NULL)
                mat->head = current->next; // Removing the head node
            else
                prev->next = current->next;
            free(current);
        }
        return;
    }

    // Create a new node for the non-zero element
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = current;

    // Insert the new node into the list
    if (prev == NULL)
    {
        mat->head = newNode; // Insert at the head of the list
    }
    else
    {
        prev->next = newNode; // Insert after the previous node
    }
}

// Display the sparse matrix in coordinate format
void displaySparseMatrix(const SparseMatrix *mat)
{
    if (mat->head == NULL)
    {
        printf("Matrix is empty\n");
        return;
    }

    Node *current = mat->head;
    printf("Row  Col  Value\n");
    while (current != NULL)
    {
        printf("%3d  %3d  %3d\n", current->row, current->col, current->value);
        current = current->next;
    }
}

// Add two sparse matrices
SparseMatrix *addSparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2)
{
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols)
    {
        printf("Matrices dimensions don't match!\n");
        return NULL;
    }

    SparseMatrix *result = createSparseMatrix(mat1->rows, mat1->cols);
    Node *p1 = mat1->head;
    Node *p2 = mat2->head;

    while (p1 != NULL || p2 != NULL)
    {
        if (p1 == NULL)
        {
            insertElement(result, p2->row, p2->col, p2->value);
            p2 = p2->next;
        }
        else if (p2 == NULL)
        {
            insertElement(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p1->row < p2->row || (p1->row == p2->row && p1->col < p2->col))
        {
            insertElement(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p2->row < p1->row || (p2->row == p1->row && p2->col < p1->col))
        {
            insertElement(result, p2->row, p2->col, p2->value);
            p2 = p2->next;
        }
        else
        {
            insertElement(result, p1->row, p1->col, p1->value + p2->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    return result;
}

SparseMatrix *subtractSparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2)
{
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols)
    {
        printf("Matrices dimensions don't match!\n");
        return NULL;
    }

    SparseMatrix *result = createSparseMatrix(mat1->rows, mat1->cols);
    Node *p1 = mat1->head;
    Node *p2 = mat2->head;

    while (p1 != NULL || p2 != NULL)
    {
        if (p1 == NULL)
        {
            insertElement(result, p2->row, p2->col, p2->value);
            p2 = p2->next;
        }
        else if (p2 == NULL)
        {
            insertElement(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p1->row < p2->row || (p1->row == p2->row && p1->col < p2->col))
        {
            insertElement(result, p1->row, p1->col, p1->value);
            p1 = p1->next;
        }
        else if (p2->row < p1->row || (p2->row == p1->row && p2->col < p1->col))
        {
            insertElement(result, p2->row, p2->col, -p2->value);
            p2 = p2->next;
        }
        else
        {
            insertElement(result, p1->row, p1->col, p1->value - p2->value);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    return result;
}

// Multiply two sparse matrices
SparseMatrix *multiplySparseMatrices(const SparseMatrix *mat1, const SparseMatrix *mat2)
{
    if (mat1->cols != mat2->rows)
    {
        printf("Matrices cannot be multiplied! Incompatible dimensions.\n");
        return NULL;
    }

    SparseMatrix *result = createSparseMatrix(mat1->rows, mat2->cols);

    for (Node *p1 = mat1->head; p1 != NULL; p1 = p1->next)
    {
        for (Node *p2 = mat2->head; p2 != NULL; p2 = p2->next)
        {
            if (p1->col == p2->row)
            {
                int row = p1->row;
                int col = p2->col;
                int value = p1->value * p2->value;
                insertElement(result, row, col, value);
            }
        }
    }

    return result;
}

// Delete the sparse matrix and free memory
void deleteSparseMatrix(SparseMatrix *mat)
{
    Node *current = mat->head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(mat);
}

int main()
{
    SparseMatrix *mat1 = NULL, *mat2 = NULL, *result = NULL;
    int choice, rows, cols, row, col, value;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Create Matrix 1\n");
        printf("2. Create Matrix 2\n");
        printf("3. Insert Element in Matrix 1\n");
        printf("4. Insert Element in Matrix 2\n");
        printf("5. Display Matrix 1\n");
        printf("6. Display Matrix 2\n");
        printf("7. Add Matrices\n");
        printf("8. Multiply Matrices\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (mat1 != NULL)
                deleteSparseMatrix(mat1); // Clean up if previously created
            printf("Enter number of rows and columns for Matrix 1: ");
            scanf("%d %d", &rows, &cols);
            mat1 = createSparseMatrix(rows, cols);
            printf("Matrix 1 created with dimensions %d x %d\n", rows, cols);
            break;

        case 2:
            if (mat2 != NULL)
                deleteSparseMatrix(mat2); // Clean up if previously created
            printf("Enter number of rows and columns for Matrix 2: ");
            scanf("%d %d", &rows, &cols);
            mat2 = createSparseMatrix(rows, cols);
            printf("Matrix 2 created with dimensions %d x %d\n", rows, cols);
            break;

        case 3:
            if (mat1 == NULL)
            {
                printf("Matrix 1 is not created yet!\n");
            }
            else
            {
                printf("Enter row, column, and value for Matrix 1: ");
                scanf("%d %d %d", &row, &col, &value);
                insertElement(mat1, row, col, value);
                printf("Element inserted into Matrix 1.\n");
            }
            break;

        case 4:
            if (mat2 == NULL)
            {
                printf("Matrix 2 is not created yet!\n");
            }
            else
            {
                printf("Enter row, column, and value for Matrix 2: ");
                scanf("%d %d %d", &row, &col, &value);
                insertElement(mat2, row, col, value);
                printf("Element inserted into Matrix 2.\n");
            }
            break;

        case 5:
            if (mat1 != NULL)
            {
                printf("Matrix 1:\n");
                displaySparseMatrix(mat1);
            }
            else
            {
                printf("Matrix 1 is not created yet!\n");
            }
            break;

        case 6:
            if (mat2 != NULL)
            {
                printf("Matrix 2:\n");
                displaySparseMatrix(mat2);
            }
            else
            {
                printf("Matrix 2 is not created yet!\n");
            }
            break;

        case 7:
            if (mat1 == NULL || mat2 == NULL)
            {
                printf("Please create both matrices before adding them!\n");
            }
            else
            {
                result = addSparseMatrices(mat1, mat2);
                if (result != NULL)
                {
                    printf("Resultant Matrix after addition:\n");
                    displaySparseMatrix(result);
                    deleteSparseMatrix(result); // Free the result matrix
                }
            }
            break;

        case 8:
            if (mat1 == NULL || mat2 == NULL)
            {
                printf("Please create both matrices before multiplying them!\n");
            }
            else
            {
                result = multiplySparseMatrices(mat1, mat2);
                if (result != NULL)
                {
                    printf("Resultant Matrix after multiplication:\n");
                    displaySparseMatrix(result);
                    deleteSparseMatrix(result); // Free the result matrix
                }
            }
            break;

        case 9:
            printf("Exiting...\n");
            if (mat1 != NULL)
                deleteSparseMatrix(mat1);
            if (mat2 != NULL)
                deleteSparseMatrix(mat2);
            return 0;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}