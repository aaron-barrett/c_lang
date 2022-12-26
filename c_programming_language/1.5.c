#include <stdio.h>

int main()
{
    printf("To see that getchar() != EOF = 1, enter any character.\n");
    printf("To see that getchar() != EOF = 0, enter CTRL-Z.\n");
    int c = (getchar() != EOF);
    printf("getchar() != EOF = %d", c);
}