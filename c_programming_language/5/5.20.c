#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUT 1000
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

void clear_output()
{
    tokentype = 0;
    token[0] = '\0';
    name[0] = '\0';
    datatype[0] = '\0';
    out[0] = '\0';
    argument[0] = '\0';
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
        printf("%s: %s %s\n", name, out, datatype);
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
        for (*p++ = c;  !isspace(c = getch()) && c !='(' && c != ')' && c != '[' && c != '\n' && c != '*' && c != ',';) /* only characters than can end a name field are spaces (default), left parenthesis and brackets, and newlines.*/
           if (isalnum(c) || c == '_')                   /* inputs only alpha-numeric characters and underscores */
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
    int type_type;
    int MAXARG = 50;
    char hold_type[MAXARG][MAXARG];
    for(int i = 0 ; i < MAXARG ; i++)
        hold_type[i][0] = '\0';
    if (tokentype == TYPE)
        strcpy(hold_type[counter++], token);
    while (gettoken() != ')'){
        if (tokentype == '*')
            strcpy(hold_type[counter++], " pointer to ");
        else if (tokentype == QUALIFIER || tokentype == TYPE)
            strcpy(hold_type[counter++], token);
        else if (tokentype == ','){
            while (counter > 0)
                strcat(hold, hold_type[--counter]);
            strcat(hold, " and ");
        }
        else if (tokentype == '('){
            char hold_func[100];
            hold_func[0] = '\0';
            char return_type[100];
            if (gettoken() == '*' && gettoken()  == NAME){
                strcpy(return_type, hold_type[--counter]);
                strcpy(hold_type[counter], "pointer to function ");
                strcat(hold_type[counter], token);
                if (gettoken() == ')' && (type_type = gettoken()) == '('){
                    strcat(hold_type[counter], " passing ");
                    func_args(hold_func);
                    strcat(hold_type[counter], hold_func);
                }
                else if (type_type == PARENS)
                    strcat(hold_type[counter], hold_func);
                strcat(hold_type[counter], " returning ");
                strcat(hold_type[counter++], return_type);
            }
            else 
                printf("Syntax error in function arguments.\n");
        }
    }
    while (counter > 0)
        strcat(hold, hold_type[--counter]);
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
    else if (tokentype == TYPE ){ /*this does not handle the initial return type which is different */
        func_args(argument);
        dirdcl();
    }
    else if (tokentype == QUALIFIER){ /* only works for qualifiers for main type */
        char datatype_hold[10];
            strcpy(datatype_hold,token);
            strcat(datatype_hold," ");
            dcl();
            strcat(out, datatype_hold);
    }
    else if (tokentype == ')'){
        if (strcmp(argument, "\0") != 0){
            strcat(out, "function passing ");
            strcat(out, argument);
            argument[0] = '\0';
            strcat(out, " returning ");
        }
        return;
    }
    else {
        printf("error :expected name or (dcl)\n");
        printf("type %c\n", tokentype);
    }
    if (tokentype != '\n')
        while ((type = gettoken())  == PARENS || type == BRACKETS)
            if (type == PARENS){
                strcat(out, " function returning ");
            }
            else if (type == BRACKETS) {
                strcat(out, " array");
                strcat(out, token);
                strcat(out, " of");
            }
    if (type == '(')
        dcl();
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