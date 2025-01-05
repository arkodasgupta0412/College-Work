#ifndef P3_H
#define P3_H

typedef struct List
{
	int *data;
	int capacity;
	int size;
} List;

// initializes an empty list
List *createList(int);

// delete the List object
void deleteList(List *);

// prints list
void print(List *);

// returns the size of list
int length(List *);

// reverses the list
void rev(List **);

// returns the element at given position, if position not exist, return -1
int get(List *, int);

// returns the index of passed element, if not found returns -1  (I will not allow user to use this)
int search(List *, int);

// modifies the element at given position, if modifies return 0, else return -1
int modify(List *, int, int);

// appends element at end of list, success -> 0, else returns -1
int append(List *, int);

// inserts the element at given position (success -> 0), if size >= capacity returns -1
int insert(List *, int, int);

// delete element of list by position, if found return element, else -1
int pop(List *, int);

// delete element of list by value, return 0, else -1
int Remove(List *, int);

// sorts list with comparator function
void sort(List **, int (*cmp)(int, int));

#endif
