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