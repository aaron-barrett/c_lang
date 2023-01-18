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
    void (*signal(int, void* (*fp)(int)))(int)
    void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int))
    void (*complex)(void (*com)(char (*(*x())[])()), void (*signal(int, void* (*fp)(int)))(int))
*/

int main()
{
    clear_output();
    while (gettoken() != EOF){
        strcat(datatype_master, token);
        dcl(out_master, name_master, argument_master);
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

/* parse function arguments */
void func_args(char* hold)
{
    int counter = 0;
    int type;
    char hold_args[MAXARG][MAXTOKEN];
    for(int i = 0 ; i < MAXARG ; i++)
        hold_args[i][0] = '\0';
    if (tokentype == TYPE)
        strcpy(hold_args[counter++], token);
    while (gettoken() != ')')
        if (tokentype == '*')
            strcpy(hold_args[counter++], " pointer to ");
        else if (tokentype == QUALIFIER)
            strcpy(hold_args[counter++], token);
        else if (tokentype == TYPE)
            strcpy(hold_args[counter++], token);
        else if (tokentype == ','){ /* this clears out everything saved for a particular agument type once we move to the next one */
            while (counter > 0)
                strcat(hold, hold_args[--counter]);
            strcat(hold, " and ");
        }
        else if (tokentype == '('){ /* this case is all for function pointers. this calls the main recursion routines for this function pointer. good luck*/
            char hold_type[MAXTOKEN];
            char hold_name[MAXTOKEN];
            char hold_argument[MAXTOKEN];
            char hold_out[MAXTOKEN];
            hold_type[0] = '\0';
            hold_name[0] = '\0';
            hold_argument[0] = '\0';
            hold_out[0] = '\0';
            /* this only counts back potential " pointer to "'s and qualifiers for the return type of the function pointer */
            strcpy(hold_type, hold_args[--counter]);
            while (counter > 0)
                strcat(hold_type, hold_args[--counter]);
            /* this is the recursive call if a function argument is itself a complex declaration, i.e., we need the code already used in dir & dirdcl, we start this recursion in dirdcl because we start with a '(' tokentype */
            dirdcl(hold_out, hold_name, hold_argument);
            strcpy(hold_args[counter], "\"");
            strcat(hold_args[counter], hold_name);
            strcat(hold_args[counter], "\"");
            strcat(hold_args[counter], ",");
            strcat(hold_args[counter], hold_out);
            strcat(hold_args[counter], hold_type);
            strcat(hold_args[counter++], ",");
            /* the below are two corner cases when you are finished with the recursion for this function pointer argument */
            if (tokentype == ')')/* avoids an off by one error by call gettoken() in the while statment*/
                break;
            if (tokentype == ','){ /* handles case where the function pointer is not the last agument*/
                while (counter > 0)
                    strcat(hold, hold_args[--counter]);
                strcat(hold, " and ");
            }
        }
    while (counter > 0)
        strcat(hold, hold_args[--counter]);
}

/* dcl: parse a declarator */
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
    else if (tokentype == TYPE ){ /*this does not handle the initial return type which is different; this is used ONLY for function arguments.*/
        func_args(argument);
        dirdcl(out,name,argument);
    }
    else if (tokentype == QUALIFIER){  /* only used for qualifiers for output type */
        char datatype_hold[10];
        strcpy(datatype_hold,token);
        strcat(datatype_hold," ");
        dcl(out,name,argument);
        strcat(out, datatype_hold);
    }
    else if (tokentype == ')'){ /* bookends the call which detects function arguements, i.e., this breaks out of detecting function arguments for good.*/
        if (strcmp(argument, "\0") != 0){
            strcat(out, " function passing ");
            strcat(out, argument);
            argument[0] = '\0';
            strcat(out, " returning ");
        }
        return; /* this seems spurious: this is the true bookend, essentially allowing us to resuse the exact functionality without function arguments.*/
    }
    else {
        printf("error :expected name or (dcl)\n");
        printf("type %c\n", tokentype);
    }
    if (tokentype != '\n')
        while ((type = gettoken())  == PARENS || type == BRACKETS)
            if (type == PARENS)
                strcat(out, " function passing nothing returning ");
            else if (type == BRACKETS) {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of ");
            }
    if (type == '('){ /* initiall detects function arguments.*/
        gettoken(); /* in this case, we merely needed to call gettoken() again; dcl(out,name,argument) can replace gettoken() & dirdcl(out,name,argument), but checking for pointers here is unnecessary with out input assumptions */
        dirdcl(out,name,argument);
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