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

    while((type = getop(s)) != 'x'){ /* The stopping condition is 'x' instead of EOF since getlines doesn't handle EOF properly. This is due to the fact that the EOF is stored as an int (good), then put into a char in a char[] (bad), then returned as an int (no longer EOF)  */
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

int getlines(char s[], int lim)
{
    int c, i;

    for(i = 0 ; (i < lim-1) && (c = getchar()) != '\n' ; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#include <ctype.h>
#define BUFSIZE 10
int buffer = 0;
int buffer_counter = 0;
char buf[BUFSIZE];  /* buffer for ungetch */
/* getop: get next operator or numeric operand */
int getop(char s[])
{
    if (buffer_counter == buffer){
        buffer_counter = 0;
        buffer = getlines(buf, BUFSIZE);
    }
    int i, c;
    while ((s[0] = buf[buffer_counter]) == ' ' || buf[buffer_counter] == '\t')
        buffer_counter++;
    s[1] = '\0';
    if ( buf[buffer_counter] >= 'A' && buf[buffer_counter] <= 'Z'){
        c = buf[buffer_counter++];
        s[0] = c;
        return VAR;
    }
    if (!isdigit(buf[buffer_counter]) && buf[buffer_counter] != '.'){
        c = buf[buffer_counter++];
        return c;       /* not a number */
    }

    i = 0;
    if (isdigit(buf[buffer_counter]))     /* collect integer part */
        while (isdigit(buf[buffer_counter])){
            s[i] = buf[buffer_counter];
            i++;
            buffer_counter++;
        }
    if (buf[buffer_counter] == '.'){ 
        s[i] = buf[buffer_counter];
        i++;
        buffer_counter++;      /* collect fraction part */
        while (isdigit(s[i] = buf[buffer_counter])){   
            i++;
            buffer_counter++;
        }
    }
    s[i] = '\0';
    return NUMBER;
}

// #define BUFSIZE 100
// char buf[BUFSIZE];  /* buffer for ungetch */
// int bufp = 0;       /* next free position in buf */

// void print_buf()
// {
//     printf("Buffer: ");
//     for(int i = 0 ;i < bufp; i++)
//         printf("%c ", buf[i]);
//     printf("End Buffer.\n");
// }

// int getch(void)     /* get a (possibly pushed back) character */
// {
//     // print_buf();
//     return (bufp > 0) ? buf[--bufp] : getchar();
// }

// void ungetch(int c) /* push character back to input */
// {
//     // print_buf();
//     if (bufp >= BUFSIZE)
//         printf("ungetch: too many characters\n");
//     else 
//         buf[bufp++] = c;
// }
