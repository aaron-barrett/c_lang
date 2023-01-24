#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXTOKEN 100
int tokentype;
char token[MAXWORD];
char previous_token[MAXWORD];
enum{NAME, TYPE, QUALIFIER, PARENS, BRACKETS};
char* qualifiers[] =    {"const", "volatile", "signed", "unsigned", "short", "long"};
char* datatypes[]  =    {"int", "double", "float", "char", "void"};


int getword(char*, int);
int gettoken(void);
int getch(void);
void ungetch(int);

int is_datatype(char s[]);
int is_qualifer(char s[]);

int main()
{
    while (tokentype != '\n'){
        gettoken();
        printf("%s", token);
    }
    return 0;
}

int gettoken(void) /* returns next token */
{
    getword(token,MAXTOKEN);
    int c;
    if (is_datatype(token) != -1)
        return tokentype = TYPE;
    else if (is_qualifer(token) != -1)
        return tokentype = QUALIFIER;
    else if (strcmp("function", token) == 0 )
    {
        getword(token, MAXTOKEN);
        if (strcmp(token, "passing") == 0)
            getword(token, MAXTOKEN);
        else {
            printf("ERROR: error in function input.\n");
            return -1;
        }
        if (strcmp(token, "nothing") == 0 ){
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else{ /* handles all argument types without any checks */
            for(int i = strlen(token) - 1 ; i >= 0; i--)
                ungetch(token[i]);
            strcpy(token,"(");
            return tokentype = '(';
        }
    }
    else if (strcmp(token, "pointer") == 0){
        getword(token,MAXTOKEN);
        if (strcmp(token, "to") == 0){
            strcpy(token, "*");
            return '*';
        }
        else {
            printf("ERROR: expected \"to\" to follow \"pointer\"\n");
            return -1;
        }
    }
    else if (strcmp(token, "returning") == 0)
    {
        if (tokentype == TYPE){
            strcpy(token, ")");
            return tokentype = ')';
        }
        else {
            gettoken(); /* possible place for recurision */
        }
    }
    else if (strcmp(token, "and") == 0 ){
        strcpy(token,",");
        return tokentype  = ',';
    }
    else if (strstr(token, "array[") != NULL){
        char* ptr = strstr(token, "[");
        int i = 0 ; 
        while (*ptr != '\0')
            token[i++] = *ptr++;
        token[i] = '\0';
        return BRACKETS;
    }
    else if (strcmp(token,"of") == 0){
        gettoken(); /* recursive call */
    }
    else if (strcmp(token, "\n") == 0)
        return tokentype = '\n';
    else{
        if (token[strlen(token)-1] == ':')
            token[strlen(token)-1] = '\0';
        else if (token[strlen(token)-1] == '\"'){
            token[strlen(token)-1] = '\0';
            for(int i = 0 ; i < strlen(token); i++)
                token[i] = token[i+1];
        }
        return tokentype = NAME;
    }
}

/* getword: get next word or character from input */
int getword(char* word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char* w = word;
    while (isspace(c = getch()) && c != '\n')
    ;
    if (c == '\n'){
        word[0] = '\n';
        word[1] = '\0';
        return word[0];
    }
    if (c != EOF)
        *w++ = c;
    for (; --lim > 0; w++)
        if (isspace(*w = getch()) || *w == ',' || *w == '.'){ /* non alpha numeric characters and underscores cancel string. */
            if (*w == ',' || *w == '.')
                break;
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
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