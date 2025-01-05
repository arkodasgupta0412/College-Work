#ifndef P4_H
#define P4_H

typedef struct Set
{
    int *data;
    int capacity;
    int size;
} Set;

// initializes an empty set
Set *createSet(int);

// deletes the set object
void deleteSet(Set *);

// prints set
void print(Set *);

// Returns the number of elements in the set.
int size(Set *);

// Returns the maximum number of elements that the set can hold.
int max_size(Set *);

// Returns whether the set is empty.
int empty(Set *);

// Adds a new element ‘g’ to the set.
int insert(Set *, int);

// Removes the value ‘g’ from the set.
int erase(Set *, int);

// Removes all the elements from the set.
void clear(Set *);

// Returns an iterator to the element ‘g’ in the set if found, else returns the iterator to the end.
int find(Set *s, int);

// Returns 1 or 0 based on whether the element ‘g’ is present in the set or not.
int count(Set *s, int);

// returns iterator to the position where the smallest element >= key is present, not found => iterator to end
int lower_bound(Set *s, int);

// returns iterator to the position where the smallest element > key is present, not found => iterator to end
int upper_bound(Set *s, int);

#endif