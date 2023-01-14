#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum{NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
int gettoken(void); 

int datatype_found = 0;
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifer name */
char datatype[MAXTOKEN];    /* data type = char, int, etc */
char out[1000];             /* output string */

int main()
{
    while (gettoken() != EOF){
        strcpy(datatype, token);
        datatype_found = 1;
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error");
        printf("%s: %s %s\n", name, out, datatype);
        datatype_found = 0;
    }
    return 0;
}

int gettoken(void) /* returns next token */
{
    int c;
    int getch(void);
    void ungetch(int);
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '('){
        while ((c = getch()) == ' ' || c == '\t') /* eliminates spurious spaces between parenthesis*/
            ;
        if (c == ')'){
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '['){
        for( *p++ = c ; (c = getch()) != ']';)
            if (isdigit(c)) /* recovers from non integer values in brackets including spaces */
                *p++ = c;
        *p++ = c;
        *p = '\0';
        return tokentype  = BRACKETS;
    }
    else if (isalpha(c)){
        for (*p++ = c;  !isspace(c = getch()) && c !='(' && c != '[' && c != '\n';){ /* only characters than can end a name field are spaces (default), left parenthesis and brackets, and newlines.*/
            if (c == '_' && (datatype_found == 1))      /* inputs underscores in name, but NOT return type - NOTE -- this exercise assumes no qualifiers */
                *p++ = c;
            else if (isalnum(c)){                       /* inputs only alpha-numeric characters  */
                *p++ = c;
            }
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;        
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;
    for(ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    if (tokentype == '('){
        dcl();
        if(tokentype != ')')
            printf("error missing ')'\n");
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else 
        printf("error :expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else{
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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