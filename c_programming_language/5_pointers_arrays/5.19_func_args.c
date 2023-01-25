/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.19: Modify undecl so that it does not add redundant parenthesis to declarations. 
*   
*   Notes: This is the expanded version of 5.19 that takes in function arguments, including complex declarations as function arguments. The 
*   user input is still symbolic, just as 5.19.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 1000

enum{NAME, TYPE, QUALIFIER, PARENS, BRACKETS};

/* We ignore storage class specifiers for the time being. We could simply add them to modifier list as is, but that might not be as clear. */
char* qualifiers[] =    {"const", "volatile", "signed", "unsigned", "short", "long"};
char* datatypes[]  =    {"int", "double", "float", "char", "void"};

int is_datatype(char s[]);
int is_qualifer(char s[]);
void clear_output(void);
int gettoken(void); 
void obtain_output(char* out );
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char out_master[MAXTOKEN];             /* output string */

/* Fun examples 
    x () * [] * () char                                                             - > char (*(*x())[])
    x (int) * [] * () char                                                          - > char (*(*x(int))[])()
    signal (int, fp * (int) * void) *  (int) void                                   - > void (*signal(int, void* (*fp)(int)))(int)
    c * (x () * [] * () char, signal (int, fp * (int) * void) *  (int) void ) void  - > void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int))

*/

int main()
{
    clear_output();
    while(gettoken() != EOF){
        obtain_output(out_master);
        printf("%s\n", out_master);
        clear_output();
    }
    return 0;
}

void obtain_output(char* out )
{
    int type;
    char temp[MAXTOKEN];
    int has_star = 0;
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
        else if (type == NAME || type == TYPE || type == QUALIFIER) /* unlike 5.20, separate qualifers for different strings are unnecessary. I'm keeping these here in case error handling is added later */
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
        else if (type == '('){
            char local_out[MAXTOKEN];
            strcpy(temp,"");
            strcat(temp, "(");
            while (gettoken() != ')'){
                local_out[0] = '\0';
                obtain_output(local_out);
                if (tokentype == ','){
                    strcat(temp, local_out);
                    strcat(temp, ",");
                }
                else 
                    strcat(temp, local_out);
                if (tokentype == ')') /* check for stopping criterion since obtain_output() changes tokentype */
                    break;
            }
            strcat(temp, ")");
            strcpy(local_out, temp); /* hold in case these arguments are for a function pointer.*/
            if (has_star)
            {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
                has_star = 0;
            }
            strcat(out,local_out);
        }
        else if (type == ')' || type == ',') /* this ends function arguments if type = ')', or individual function arguments if type = ','*/
            return;
        else 
            printf("invalid input at %s\n", token);
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
            if (isdigit(c)) /* recovers from non integer values in brackets. */
                *p++ = c;
        *p++ = c;
        *p = '\0';
        return tokentype  = BRACKETS;
    }
    else if (isalpha(c)){
        for (*p++ = c;  isalnum(c = getch()) || c == '_';) /* only characters than can end a name field are spaces (default), left parenthesis and brackets, and newlines.*/
            *p++ = c;
        *p = '\0';
        ungetch(c);
        if (is_datatype(token) != -1)
            return tokentype = TYPE;
        else if (is_qualifer(token) != -1)
            return tokentype = QUALIFIER;
        else
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

/* checks if a string is a defined datatype */
int is_datatype(char s[]){ 
    for(int i = 0 ; i < sizeof(datatypes) / sizeof(datatypes[0]); i++)
        if (strcmp(s, datatypes[i]) == 0)
            return i;
    return -1;
}

/* checks if a string is a defined qualifier */
int is_qualifer(char s[]){ 
    for(int i = 0 ; i < sizeof(qualifiers) / sizeof(qualifiers[0]); i++)
        if (strcmp(s, qualifiers[i]) == 0)
            return i;
    return -1;
}

/* resets variables for the next input */
void clear_output(void)
{
    tokentype = 0;
    token[0] = '\0';
    out_master[0] = '\0';
}