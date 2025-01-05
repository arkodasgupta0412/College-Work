/*
5. Write a program to generate 1,00,000 random strings of capital letters of length 10 each, without
repetitions and store them in a file in character mode one string per line
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>


// Uniqueness with Binary Search Tree
struct Node {
    long long val;
    struct Node* left;
    struct Node* right;
};


bool search(struct Node* node, long long target) {
    if (node == NULL) {
        return false;
    }

    if (node->val == target) {
        return true;
    }

    bool result = false;

    if (target < node->val) {
        result = result || search(node->left, target);
    } else {
        result = result || search(node->right, target);
    }

    return result;
}


struct Node* append(struct Node* node, long long value) {
    if (node == NULL) {
        struct Node* p = (struct Node *) malloc(sizeof(struct Node));
        p->val = value;
        p->left = NULL;
        p->right = NULL;
        return p;
    }

    if (value < node->val) {
        node->left = append(node->left, value);
    } else {
        node->right = append(node->right, value);
    }

    return node;
}


long long hashedString(char *str, int n) {
    long long hash = 0;

    for (int i = 0; i < n; i++) {
        hash = hash*26 + (str[i] - 'a');
    }

    return hash;
}


void dfsForFreeing(struct Node* node) {
    if (node == NULL) {
        return;
    }

    dfsForFreeing(node->left);
    dfsForFreeing(node->right);

    free(node);
}


int main() {
    const int N = 100000;
    char str[11];
    str[10] = '\0';
    srand(time(NULL));
    int cnt = 0;

    struct Node *root = NULL;

    FILE *fp = fopen("output.txt", "w");

    while(cnt < N) {
        for (int j = 0; j < 10; j++) {
            str[j] = 'a' + (rand() % 26);

        }

        long long hash = hashedString(str, 10);

        bool found = search(root, hash);
        if (!found) {
            fprintf(fp, "%s\n", str);
            append(root, hash);
            cnt++;
        }
    }

    fclose(fp);
    dfsForFreeing(root);

    return 0;
}
