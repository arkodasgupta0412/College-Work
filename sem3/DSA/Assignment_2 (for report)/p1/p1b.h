/*
2.1. Define an ADT for Polynomials.
Write C data structure representation and functions for the operations on the Polynomials in a Header file.
Write a menu-driven main program in a separate file for testing the different operations and include the
above header file.
*/


#ifndef P1B_H
#define P1B_H

typedef struct PolyNode
{
    double coeff;
    int exp;
    struct PolyNode *next;

} PolyNode;

PolyNode *createNode(double, int);
PolyNode *createPoly(int);
void insert(PolyNode **, double, int);
PolyNode *add(PolyNode *, PolyNode *);
PolyNode *sub(PolyNode *, PolyNode *);
PolyNode *mul(PolyNode *, PolyNode *);
void printPoly(PolyNode *);

#endif