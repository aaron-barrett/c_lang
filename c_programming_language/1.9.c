#include<stdio.h>

int main()
{
    int c;
    int blanks = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ')
            ++blanks;
        else {
            if (blanks != 0){
                putchar(' ');
                blanks = 0;
            }
            putchar(c);
        }
    return 0;
}