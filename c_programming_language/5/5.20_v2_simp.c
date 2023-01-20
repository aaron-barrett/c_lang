#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 10000
#define MAXARG 10

enum{NAME, TYPE, QUALIFIER, PARENS, BRACKETS};

/* Might want to add functionality to expand these. right now structs can't be used, and this assumes that all qualifiers appear after a datatype, and that shorthand where a qualifier alone is used for a type is error prone if not unusable */
char* qualifiers[] =    {"const", "volatile", "signed", "unsigned", "short", "long"};
char* datatypes[]  =    {"int", "double", "float", "char", "void"};

int is_datatype(char s[]);
int is_qualifer(char s[]);
void remove_space(char s[]);
void clear_output();

void dcl(char* out, char* name, char* argument);
void dirdcl(char* out, char* name, char* argument);
void func_args(char* hold);
void obtain_return_type(char* hold);
int gettoken(void); 

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name_master[MAXTOKEN];        /* identifer name */
char datatype_master[MAXTOKEN];    /* data type = char, int, etc */
char out_master[MAXTOKEN];             /* output string */
char argument_master[MAXTOKEN];             /* output string */
char final_output[MAXTOKEN];             /* output string */

/*  Fun test examples
    int (*x)(int*const,void*(*y)(int))
    char (*(*x())[])()
    void (**de[])(int,int);
    void (*signal(int, void* (*fp)(int)))(int)
    void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int))
    void (*complex)(void (*com)(char (*(*x())[])()), void (*signal(int, void* (*fp)(int)))(int))
*/

int main()
{
    clear_output(); /* clear out input strings just to be safe. NOTE: putting first in the while loop clears out type. */
    while (gettoken() != EOF){
        obtain_return_type(datatype_master); /* obtains the type */
        dirdcl(out_master, name_master, argument_master);
        if (tokentype != '\n')
            printf("syntax error\t tokentype: %c\n", tokentype);
        strcat(final_output,name_master);
        strcat(final_output, ": ");
        strcat(final_output, out_master);
        strcat(final_output, datatype_master);
        remove_space(final_output);
        printf("%s\n",final_output);
        clear_output();
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

void obtain_return_type(char* hold)
{
    char datatype_hold[MAXARG][MAXTOKEN];
    for(int i = 0 ; i < MAXARG; i ++)
        datatype_hold[i][0] = '\0';
    int counter = 0;
    strcpy(datatype_hold[counter++],token);
    while (gettoken() == '*' || tokentype == QUALIFIER){
        if (tokentype == QUALIFIER){
            strcat(token, " ");
            strcpy(datatype_hold[counter++],token);
        }
        else
            strcpy(datatype_hold[counter++]," pointer to ");
    }
    while (counter > 0 )
        strcat(hold, datatype_hold[--counter]);
    /* tokentype should now be NAME or '(' */
}

/* parse function arguments */
/* 
    This is a vastly improved version of func_args from the previous version. This streamlines all calls for function arguments, and returns precisely to the hanging '(' in dirdcl which triggers this call. This streamline is why the obtain_return type function exists; it means we only use dcl for function pointers. 
*/
void func_args(char* hold)
{
    char hold_args[MAXTOKEN];
    hold_args[0] = '\0';
    char hold_type[MAXTOKEN];
    char hold_name[MAXTOKEN];
    char hold_argument[MAXTOKEN];
    char hold_out[MAXTOKEN];
    while (gettoken() != ')'){
        hold_type[0] = '\0';
        hold_name[0] = '\0';
        hold_argument[0] = '\0';
        hold_out[0] = '\0';
        /* this only counts back potential " pointer to "'s and qualifiers for the return type of the function pointer, just like the initial call in main */
        obtain_return_type(hold_type); /* obtains the type */
        /* this is the recursive call if a function argument is itself a complex declaration, i.e., we need the code already used in dir & dirdcl, we start this recursion in dirdcl because we start with a '(' tokentype */
        if (tokentype != ',' && tokentype != ')'){ /* only call dirdcl if there are more function arguments; this means you will have a name and out field as well*/
            dirdcl(hold_out, hold_name, hold_argument);
            strcpy(hold_args, "\"");
            strcat(hold_args, hold_name);
            strcat(hold_args, "\"");
            strcat(hold_args, ",");
            strcat(hold_args, hold_out);
            strcat(hold_args, hold_type);
            strcat(hold_args, ",");
        }
        else 
            strcpy(hold_args, hold_type);
        strcat(hold, hold_args); /* this saves the hold_args to the hold string, which is the outut of this function */
        /* the below are three corner cases when you are finished with the recursion for this function pointer argument */
        if (tokentype == ')') /* avoids an off by one error by call gettoken() in the while statment*/
            break;
        if (tokentype == ',') /* handles case where the function pointer is not the last agument*/
            strcat(hold, " and ");
    }
}

/* dcl: parse a declarator; NOTE: this now only handles pointers to functions */
void dcl(char* out, char* name, char* argument)
{
    int ns;
    for(ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl(out,name,argument);
    while(ns-- > 0)
        strcat(out, " pointer to ");
}

/* dirdcl: parse a direct declarator */
void dirdcl(char* out, char* name, char* argument)
{
    int type;
    if (tokentype == '('){
        dcl(out,name,argument);
        if(tokentype != ')'){
            printf("error missing ')' \n");
            printf("type %d\n", tokentype);
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else if (tokentype == ',') /* used when dirdcl is used for function arguments */
        return;
    else 
        printf("error :expected name or (dcl)\ttokentype = %c\n", tokentype);
    while ((type = gettoken())  == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function passing nothing returning ");
        else if (type == BRACKETS) {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of ");
        }
    if (type == '('){ /*detects function arguments. */
        func_args(argument);
        if (tokentype == ')'){
            strcat(out, " function passing ");
            strcat(out, argument);
            argument[0] = '\0';
            strcat(out, " returning ");
            gettoken(); /* obtains the next token.*/
        }
        else 
            printf("Syntax error in function argument.\n");
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

int is_datatype(char s[]){
    for(int i = 0 ; i < sizeof(datatypes) / sizeof(datatypes[0]); i++)
        if (strcmp(s, datatypes[i]) == 0)
            return i;
    return -1;
}

int is_qualifer(char s[]){
    for(int i = 0 ; i < sizeof(qualifiers) / sizeof(qualifiers[0]); i++)
        if (strcmp(s, qualifiers[i]) == 0)
            return i;
    return -1;
}

void remove_space(char s[])
{
    int k = 0;
    while (isspace(s[0])){
        while (s[k] != '\0')
            s[k++] = s[k+1];
        k = 0;
    }
    for(int i = 0 ; s[i+1] != '\0'; i++ )
        while (isspace(s[i]) && isspace(s[i+1]))
            for(k = i ; s[k] != '\0' ; k++)
                s[k] = s[k+1];
}

void clear_output()
{
    tokentype = 0;
    token[0] = '\0';
    name_master[0] = '\0';
    datatype_master[0] = '\0';
    out_master[0] = '\0';
    argument_master[0] = '\0';
    final_output[0] = '\0';
}