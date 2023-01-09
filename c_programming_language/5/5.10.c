#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100 
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
double expr(int argc, char* s[]);

int main(int argc, char* argv[])
{
    printf("argc = %d \t argv = ", argc);
    for(int i = 1 ; i < argc ; i++)
        printf("%s ", argv[i]);
    printf("\n");

    if (argc == 1)
        printf("No expression to evaluate\n");
    else
        printf("arvg = %f\n", expr(argc, argv));

    return 0;
}

double expr(int argc, char* s[])
{
    int op2;
    int type;
    int counter = 1;
    while(counter != argc){
        type = getop(s[counter]);
        switch (type){
            case NUMBER:
                push(atof(s[counter]));
                break;
            case '+':
                push(pop() + pop());
                break;
            case 'x':
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
            case ' ':
                break;
            case '\n':
                break;
            default:
                printf("error: unknown command %s\n",s[counter]);
        }
        counter++;
    }
    return pop();
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

#include <ctype.h>
/* geto: get next operator or numeric operand */
int getop(char s[])
{
    int counter = 0;
    while (s[counter]  == ' ' || s[counter] == '\t')
        counter++;
    if (!isdigit(s[counter]) && s[counter] != '.')
        return s[counter];       /* not a number */
    if (isdigit(s[counter]))     /* collect integer part */
        while (isdigit(s[++counter]))
            ;
    if (s[counter] == '.')    /* collect fraction part */
        while (isdigit(s[++counter] ))
            ;
    s[counter] = '\0';
    return NUMBER;
}
