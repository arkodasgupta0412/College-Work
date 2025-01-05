#include <stdio.h>
#include <string.h>
#include "stack.c"
#define LEN 100

int main()
{
    char s[LEN];
    printf("Enter parentheses string: ");
    scanf("%s", s);
    int ans = 0;

    Stack *st = (Stack *)malloc(sizeof(Stack));
    init_s(st);
    push(st, '\0');

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(')
            push(st, s[i]);

        else
        {
            if (top(st) == '(')
            {
                pop(st);
                ans += 2;
            }
            else
                push(st, s[i]);
        }
    }

    printf("Output: %d\n", ans);
}