#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int main()
{
    int c;
    while ((c = getch()) != EOF)
        if (isalnum(c))
            printf("%c is alnum\n", c);
        else if (!isalnum(c))
            printf("%c is !alnum\n", c);
        else 
            printf("%c is not alnum and not !isalnum\n", c);
    return 0;
}


#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c) /* push character back to input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}