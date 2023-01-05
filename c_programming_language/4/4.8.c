#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <float.h>

#define MAXOP 100 
#define NUMBER '0'
#define VAR '1'
#define RECENT '2'
#define MAXVAR 26


int getop(char []);
void push(double);
double pop(void);
int return_stack_size(void);
double vars[MAXVAR];

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int skip_pop = 0;
    double recent;
    for(int i = 0 ; i < MAXVAR; i++)
        vars[i] = DBL_MAX;
    while((type = getop(s)) != EOF){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case VAR: /* handles saving and using variables */
                if (vars[s[0] - 'A'] == DBL_MAX){
                    vars[s[0] - 'A'] = pop();
                    recent = vars[s[0] - 'A'];
                    printf("\t%0.8g\n", recent);
                    skip_pop = 1;
                }
                else {
                    push(vars[s[0] - 'A']);
                    vars[s[0] - 'A'] = DBL_MAX;
                }
                break;
            case 'r': /* Use last value */
                push(recent);
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
            case 'p': /* print top value  */
                printf("\t%.8g\n", recent);
                skip_pop = 1;
                break;
            case 'v':
                for(int i = 0 ; i < MAXVAR ; i++)
                    printf("\t%d ", vars[i]);
                printf("\n");
                skip_pop = 1;
                break;
            case 'd':
                op2 = pop();
                push(op2);
                push(op2);
                skip_pop = 0;
                break;
            case 's': /* swap top two values*/
                op2 = pop();
                double op3 = pop();
                push(op2);
                push(op3);
                break;
            case 'c': /* clear stack*/
                while (return_stack_size() != 0)
                    pop();
                skip_pop = 1;
                printf("Stack Cleared.\n");
                break;
            case 'i': /* sin */
                push(sin(pop()));
                break;
            case 'o': /* cos */
                push(cos(pop()));
                break;
            case 'e': /* exp*/
                push(exp(pop()));
                break;
            case 'w': /* power */
                push(pow(pop(),pop()));
                break;
            case '\n':
                if (skip_pop){
                    skip_pop = 0;
                    break;
                }
                else {
                    recent = pop();
                    printf("\t%.8g\n", recent);
                }
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
/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
    s[1] = '\0';
    if (c >= 'A' && c <= 'Z'){
        s[0] = c;
        return VAR;
    }
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
void print_buf()
{
    printf("Buffer: ");
    for(int i = 0 ;i < bufp; i++)
        printf("%c ", buf[i]);
    printf("End Buffer.\n");
}

int getch(void)     /* get a (possibly pushed back) character */
{
    print_buf();
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back to input */
{
    // print_buf();
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}
