/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.1: As written, getint treats a + or a - not followed by a digit as a valid representation of zero. Fix it to push such a character back
*   on the input.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int getint(int *pn)
{
    int c, sign;
    int plus_minus;
    while (isspace(c = getch()))
    ;
    if (!isdigit(c) && c != EOF && c!= '-' && c != '+'){
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-'){
        plus_minus = c;
        if (!isdigit(c = getch())){
            ungetch(plus_minus);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 10
int main()
{
    int n, array[SIZE], getint(int *);
    for(n = 0; n < SIZE && getint(&array[n]) != EOF ; n++)
    ;
    for(int i = 0 ; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
    return 0;
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push number back to input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
