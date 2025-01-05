/*
Develop a recursive program for generating all the permutations of the
letters ‘a’ to ‘f’ with repetitions taking 3, 4, 5 and 6 characters.
*/


#include <stdio.h>
#include <stdlib.h>


void rec(char letters[], char *word, int index, int n) {
    if (index == n) {
        printf("%s\n", word);
        return;
    }

    for (int i = 0; i < 6; i++) {
        word[index] = letters[i];
        rec(letters, word, index + 1, n);
    }
}


void generatePermutations(int n) {
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    char *word = (char *)malloc((n + 1) * sizeof(char));
    word[n + 1] = '\0';

    rec(letters, word, 0, n);

    free(word);
}


int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    generatePermutations(n);
}
