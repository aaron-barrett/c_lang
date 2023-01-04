#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <float.h>

#define MAXOP 100 
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
int return_stack_size(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int skip_pop = 0;
    while((type = getop(s)) != EOF){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else 
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 < 0)
                    op2 = -op2;
                push((int)pop() % (int)op2);
                break;
            case 'p':
                op2 = pop();
                printf("\t%.8g\n", op2);
                push(op2);
                skip_pop = 1;
                break;
            case 'd':
                op2 = pop();
                push(op2);
                push(op2);
                skip_pop = 0;
                break;
            case 's':
                op2 = pop();
                double op3 = pop();
                push(op2);
                push(op3);
                break;
            case 'c':
                while (return_stack_size() != 0)
                    pop();
                skip_pop = 1;
                printf("Stack Cleared.\n");
                break;
            case '\n':
                if (skip_pop){
                    skip_pop = 0;
                    break;
                }
                else 
                    printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n",s);
        }
    }
    return 0;
}

#define MAXVAL 100 /* maximum depth of val stack*/
int sp = 0;        /* next free stack position*/
double val[MAXVAL]; /* value stack*/
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n",f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int return_stack_size(void)
{
    return sp;
}

#include <ctype.h>
int getch(void);
void ungetch(int);
/* geto: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
