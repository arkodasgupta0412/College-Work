/*
Write a C program to solve the n-queens problem. The value of n may be
between 8 and 1000. We are interested in finding the first achieved solution
only. (not all the solutions)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int** createBoard(int n) {
    int** board = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        board[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    return board;
}

char** createQBoard(int n) {
    char** Qboard = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        Qboard[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            Qboard[i][j] = '.';
        }
    }
    return Qboard;
}

void freeBoard(void** board, int n) {
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

void printBoard(char** Qboard, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", Qboard[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void markQueen(int** board, int n, int row, int col, int increment) {
    for (int i = 0; i < n; i++) {
        board[i][col] += increment;
    }
    for (int j = 0; j < n; j++) {
        board[row][j] += increment;
    }

    int i, j;
    
    i = row; j = col;
    while (i < n && j < n) {
        board[i][j] += increment;
        i++; j++;
    }

    i = row; j = col;
    while (i >= 0 && j < n) {
        board[i][j] += increment;
        i--; j++;
    }

    i = row; j = col;
    while (i < n && j >= 0) {
        board[i][j] += increment;
        i++; j--;
    }

    i = row; j = col;
    while (i >= 0 && j >= 0) {
        board[i][j] += increment;
        i--; j--;
    }
}

void solveQueensRec(int** board, int n, int row, char** Qboard) {
    if (row >= n) {
        printBoard(Qboard, n);
        freeBoard((void**)board, n);
        freeBoard((void**)Qboard, n);

        printf("Time elapsed: %.2f s\n", (double)clock() / CLOCKS_PER_SEC);
        exit(0);
    }

    for (int col = 0; col < n; col++) {
        if (board[row][col] == 0) {
            Qboard[row][col] = 'Q';
            markQueen(board, n, row, col, 1);

            solveQueensRec(board, n, row + 1, Qboard);

            markQueen(board, n, row, col, -1);
            Qboard[row][col] = '.';
        }
    }
}

void solveNQueens(int n) {
    int** board = createBoard(n);
    char** Qboard = createQBoard(n);

    solveQueensRec(board, n, 0, Qboard);

    freeBoard((void**)board, n);
    freeBoard((void**)Qboard, n);
}


int main() {
    int n;
    printf("Enter the value of n ( <= 1000): ");
    scanf("%d", &n);

    if (n > 1000) {
        printf("Invalid value of n. Please choose a value less than 1000.\n");
        return 1;
    }
    
    solveNQueens(n);

    printf("Time elapsed: %.2f s\n", (double)clock() / CLOCKS_PER_SEC);

    return 0;
}
