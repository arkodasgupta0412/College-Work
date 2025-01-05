#include <stdio.h>
#include <stdlib.h>
#include "../p8.c"

Node *build_List(FILE *fp)
{
    int num;
    Node *head = init_l(), *prev = NULL;

    while (fscanf(fp, "%d, ", &num) != EOF)
    {
        Node *node = createNode(num);
        if (prev == NULL)
        {
            insert_front(node, &head);
        }
        else
        {
            insert_after(node, &prev);
        }
        prev = node;
    }
    return head;
}

Node *build_List_Reverse(FILE *fp)
{
    int num;
    rewind(fp);
    Node *head = init_l();

    while (fscanf(fp, "%d, ", &num) == 1)
    {
        Node *node = createNode(num);
        insert_front(node, &head);
    }
    return head;
}

int main()
{
    FILE *fp;
    int num;
    if ((fp = fopen("data.txt", "r")) == NULL)
    {
        printf("Cannot open file\n");
        exit(1);
    }

    Node *l1 = build_List(fp);
    printf("\nNumbers read from file: \n\n");
    print(l1);

    Node *l2 = build_List_Reverse(fp);
    printf("\nNumbers read from file in reverse order: \n\n");
    print(l2);

    fclose(fp);
    return 0;
}