#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000
#define MAXARG 10

enum{NAME, TYPE, QUALIFIER, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
int gettoken(void); 

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifer name */
char datatype[MAXTOKEN];    /* data type = char, int, etc */
char out[MAXOUT];             /* output string */
char argument[MAXOUT];             /* output string */
char final_output[MAXOUT];             /* output string */

// #define MAXKEYWORD 10 // for adding in option for user to input defined datatype, this would mean the "find" functiosn need changing, and this really just substitutes a robust "struct" functionality.
char* qualifiers[] =    {"const", "volatile", "signed", "unsigned", "short", "long"};
char* datatypes[]  =    {"int", "double", "float", "char", "void"};

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
    name[0] = '\0';
    datatype[0] = '\0';
    out[0] = '\0';
    argument[0] = '\0';
    final_output[0] = '\0';
}

int main()
{
    clear_output();
    while (gettoken() != EOF){
        strcat(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\t tokentype: %c\n", tokentype);
        strcat(final_output,name);
        strcat(final_output, ": ");
        strcat(final_output, out);
        strcat(final_output, datatype);
        /* thes prettify the output */
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
            strcpy(hold_args[counter], token);
        else if (tokentype == TYPE)
            strcpy(hold_args[counter++], token);
        else if (tokentype == ','){
            while (counter > 0)
                strcat(hold, hold_args[--counter]);
            strcat(hold, " and ");
        }
        else if (tokentype == '('){
            char hold_func[100];
            hold_func[0] = '\0';
            char return_type[100];
            if (gettoken() == '*' && gettoken()  == NAME){
                strcpy(return_type, hold_args[--counter]);
                strcpy(hold_args[counter], " pointer to function ");
                strcat(hold_args[counter], "\""); /* quotes prettify the function name*/
                strcat(hold_args[counter], token);
                strcat(hold_args[counter], "\"");
                if (gettoken() == ')' && (type = gettoken()) == '('){
                    strcat(hold_args[counter], " passing ");
                    func_args(hold_func);
                    strcat(hold_args[counter], hold_func);
                }
                else if (type == PARENS)
                    strcat(hold_args[counter], hold_func);
                strcat(hold_args[counter], " returning ");
                strcat(hold_args[counter++], return_type);
            }
            else 
                printf("Syntax error in function arguments.\n");
        }
    while (counter > 0)
        strcat(hold, hold_args[--counter]);
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;
    for(ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out, " pointer to ");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    if (tokentype == '('){
        dcl();
        if(tokentype != ')'){
            printf("error missing ')' \n");
            printf("type %d\n", tokentype);
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else if (tokentype == TYPE ){ /*this does not handle the initial return type which is different; this is used ONLY for function arguments.*/
        func_args(argument);
        dirdcl();
    }
    else if (tokentype == QUALIFIER){  /* only used for qualifiers for output type */
        char datatype_hold[10];
        strcpy(datatype_hold,token);
        strcat(datatype_hold," ");
        dcl();
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
                strcat(out, " function returning ");
            else if (type == BRACKETS) {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of ");
            }
    if (type == '('){ /* initiall detects function arguments.*/
        gettoken(); /* in this case, we merely needed to call gettoken() again; dcl() can replace gettoken() & dirdcl(), but checking for pointers here is unnecessary with out input assumptions */
        dirdcl();
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