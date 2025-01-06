/*
2.13. Implement an application to find out the Inverted Index of a set of text files, given a set of keywords.
Create a set of 6 text files having the keywords in different positions in the text files. The keywords may
occur multiple times in a file. The inverted index file will list the key words along with the file names in
which they occur and how many times they occur in that file.
*/


#include <stdio.h>
#include <string.h>
#define MAX 100

void write(const char *keyword, int count[])
{
    FILE *fp;
    fp = fopen("inverted_index.txt", "a");

    fprintf(fp, "%s ", keyword);
    for (int i = 0; i < 6; i++)
    {
        fprintf(fp, "%d ", count[i]);
    }
    fprintf(fp, "%s", "\n");
}

void search(int suffix, const char *keyword, int *cnt)
{
    FILE *fp;
    char filename[MAX], word[MAX];
    sprintf(filename, "file%d.txt", suffix);

    fp = fopen(filename, "r");

    while (fscanf(fp, "%s", word) != EOF)
    {
        if (!strcmp(word, keyword))
            (*cnt)++;
    }

    fclose(fp);
}

int main()
{
    int n;

    printf("Enter number of keywords: ");
    scanf("%d", &n);

    char keyword[n][MAX];

    printf("Enter %d keywords in new lines:\n", n);
    for (int i = 0; i < n; i++)
    {
        int count[6];
        scanf("%s", keyword[i]);
        for (int j = 1; j <= 6; j++)
        {
            int cnt = 0;
            search(j, keyword[i], &cnt);
            count[j - 1] = cnt;
        }
        write(keyword[i], count);
    }
}