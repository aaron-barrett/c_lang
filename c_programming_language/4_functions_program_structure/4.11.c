/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.11: Modify getop so that it doesn't need to use ungetch. Hint: Use an internal static variable.
*   
*   Notes:
*********************************************************************************************************************************************/
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
int check_var(char c);
void set_var(char c, double d);
double return_var(char c);
void initialize_vars(void);
void print_vars(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int skip_pop = 0;
    double recent;
    initialize_vars();

    while((type = getop(s)) != EOF){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case VAR: /* handles saving and using variables */
                if (check_var(s[0]) == 1){
                    recent = pop();
                    set_var(s[0], recent);
                    printf("\t%0.8g\n", recent);
                    skip_pop = 1;
                }
                else 
                    push(return_var(s[0]));
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
            case 'v': /* print vars */
                print_vars();
                skip_pop = 1;
                break;
            case 'r': /* Use last value */
                push(recent);
                break;
            case 'd': /* double top stack value*/
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

double vars[MAXVAR];

void initialize_vars(void){
    for(int i = 0 ; i < MAXVAR; i++)
        vars[i] = DBL_MAX;
}

void print_vars(void){
    for(int i = 0 ; i < MAXVAR ; i++)
        printf("\t%.8g ", vars[i]);
    printf("\n");
}

double return_var(char c){
    double hold = vars[c - 'A'];
    vars[c - 'A'] = DBL_MAX;
    return hold;
}

int check_var(char c){
    return (vars[c - 'A'] == DBL_MAX);
}

void set_var(char c, double d){
        vars[c - 'A'] = d;
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
int getch(char buf[]);
void ungetch(int);
#define BUFSIZE 100
int bufp = 0; 

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    static char buf[BUFSIZE];
    int i, c;
    while ((s[0] = c = getch(buf)) == ' ' || c == '\t')
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
        while (isdigit(s[++i] = c = getch(buf)))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch(buf)))
            ;
    s[i] = '\0';
    if (c != EOF){
        if (bufp >= BUFSIZE)
            printf("Too many characters\n");
        else 
            buf[bufp++] = c;
    }
    return NUMBER;
}

int getch(char buf[])  /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
