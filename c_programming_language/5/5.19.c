#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum{NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);

int gettoken(void); 
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifer name */
char datatype[MAXTOKEN];    /* data type = char, int, etc */
char out[1000];             /* output string */

int main()
{
    int type;
    char temp[MAXTOKEN];
    int has_star = 0;
    while(gettoken() != EOF){
        strcpy(out, token);
        while((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS){
                if (has_star){
                    sprintf(temp, "(*%s)", out);
                    strcpy(out, temp);
                    has_star = 0;                
                }
                strcat(out, token);
            }
            else if (type == '*'){
                if (has_star) /* this sets has_star in order to check for spurious parenthesis; they are only added if the following command is a bracket or parenthesis. */
                {
                    sprintf(temp, "*%s", out);
                    strcpy(out, temp);
                }
                has_star = 1;
            }
            else if (type == NAME)
            {
                if (has_star)
                {
                    sprintf(temp, "*%s", out);
                    strcpy(out, temp);
                    has_star = 0;
                }
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else 
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
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
        if ((c = getch()) == ')'){
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '['){
        for( *p++ = c ; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype  = BRACKETS;
    }
    else if (isalpha(c)){
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;        
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