/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.2: Write getfloat, the floating-point analog of getint. What types does getfloat return as its function value?
*   
*   Notes: Still returns int. No need to change it.
*********************************************************************************************************************************************/
#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn)
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
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.'){
        float power = 1.0;
        c = getchar();
        for (; isdigit(c); c = getch()){
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;
        }
        *pn /= power;
    }
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 10
int main()
{
    int n, getfloat(float *);
    float array[SIZE];
    for(n = 0; n < SIZE && getfloat(&array[n]) != EOF ; n++)
    ;
    for(int i = 0 ; i < n; i++)
        printf("%f ", array[i]);
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
