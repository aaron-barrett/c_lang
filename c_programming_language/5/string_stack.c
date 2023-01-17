#include <stdio.h>
#include <string.h>

#define MAXVAL 100 /* maximum depth of val stack*/
int sp = 0;        /* next free stack position*/
char* q_stack[MAXVAL]; /* value stack*/

void push(char* f)
{
    if (sp < MAXVAL)
        q_stack[sp++] = f;
    else 
        printf("error: stack full, can't push %g\n",f);
}

char* pop(void)
{
    if (sp > 0)
        return q_stack[--sp];
    else {
        printf("error: stack empty\n");
        return "";
    }
}

int obtain_index(void)
{
    return sp;
}

int main()
{
    char s[] = "first";
    char t[] = "second";
    push(s);
    push(t);
    while(obtain_index() != 0)
        printf("%s\n", pop());

    char ss[10];
    ss[0] = '\0';
    char tt[10] = "ass";
    if (strcmp(ss, "\0") != 0)
        printf("%s \t %s \n", ss,tt);

    return 0;
}