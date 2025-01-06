/*
2.1. Define an ADT for Polynomials.
Write C data structure representation and functions for the operations on the Polynomials in a Header file.
Write a menu-driven main program in a separate file for testing the different operations and include the
above header file.
*/


#include <stdio.h>
#include <stdlib.h>
#include "p1b.h"

PolyNode *createNode(double coeff, int exp)
{
    PolyNode *node = (PolyNode *)malloc(sizeof(PolyNode));
    node->coeff = coeff;
    node->exp = exp;
    node->next = NULL;

    return node;
}

void insert(PolyNode **head, double coeff, int exp)
{
    PolyNode *newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp)
    {
        // Insert at the head if the list is empty or the new node has the highest exponent
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        // Finding appropriate position for insert
        PolyNode *temp = *head;
        while (temp->next != NULL && temp->next->exp > exp)
        {
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->exp == exp)
        {
            // If a node with the same exponent exists, add coefficients
            temp->next->coeff += coeff;
            free(newNode);
        }
        else
        {
            // Insert in the middle or end
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

PolyNode *createPoly(int n)
{
    double coeff;
    int exp;
    PolyNode *head = NULL;

    for (int i = 1; i <= n; i++)
    {
        printf("Enter coefficient and exponent for term %d: ", i);
        scanf("%lf %d", &coeff, &exp);
        insert(&head, coeff, exp);
    }
    return head;
}

PolyNode *add(PolyNode *p1, PolyNode *p2)
{
    PolyNode *temp1 = p1, *temp2 = p2;
    PolyNode *res = NULL;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->exp > temp2->exp)
        {
            insert(&res, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        }
        else if (temp1->exp < temp2->exp)
        {
            insert(&res, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        }
        else
        {
            insert(&res, temp1->coeff + temp2->coeff, temp2->exp);
            temp1 = temp1->next, temp2 = temp2->next;
        }
    }

    while (temp1 != NULL)
    {
        insert(&res, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        insert(&res, temp2->coeff, temp1->exp);
        temp2 = temp2->next;
    }

    return res;
}

PolyNode *sub(PolyNode *p1, PolyNode *p2)
{
    PolyNode *temp1 = p1, *temp2 = p2;
    PolyNode *res = NULL;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->exp > temp2->exp)
        {
            insert(&res, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        }
        else if (temp1->exp < temp2->exp)
        {
            insert(&res, -temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        }
        else
        {
            insert(&res, temp1->coeff - temp2->coeff, temp2->exp);
            temp1 = temp1->next, temp2 = temp2->next;
        }
    }

    while (temp1 != NULL)
    {
        insert(&res, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        insert(&res, -temp2->coeff, temp1->exp);
        temp2 = temp2->next;
    }

    return res;
}

PolyNode *mul(PolyNode *p1, PolyNode *p2)
{
    PolyNode *temp1 = p1, *temp2;
    PolyNode *res = NULL;

    while (temp1 != NULL)
    {
        temp2 = p2;
        while (temp2 != NULL)
        {
            insert(&res, temp1->coeff * temp2->coeff, temp1->exp + temp2->exp);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    return res;
}

void printPoly(PolyNode *poly)
{
    PolyNode *temp = poly;
    while (temp->next)
    {
        printf("(%.1lf)x^(%d) + ", temp->coeff, temp->exp);
        temp = temp->next;
    }
    printf("(%.1lf)x^(%d)\n", temp->coeff, temp->exp);
}

int main()
{
    PolyNode *p1 = createPoly(4);
    printf("\np1(x) = ");
    printPoly(p1);
    printf("\n");
    PolyNode *p2 = createPoly(3);
    printf("\np2(x) = ");
    printPoly(p2);

    PolyNode *sum = add(p1, p2);
    printf("\np1(x) + p2(x) = ");
    printPoly(sum);

    PolyNode *diff = sub(p1, p2);
    printf("\np1(x) - p2(x) = ");
    printPoly(diff);

    PolyNode *p = mul(p1, p2);
    printf("\np1(x) * p2(x) = ");
    printPoly(p);
}