/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.19: Modify undecl so that it does not add redundant parenthesis to declarations. 
*   
*   Notes: This is 5.19_func_args which takes the full output of 5.20 and returns the symbolic declaration. This is the second crown jewel
*   of this solution set along with 5.20.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 1000

enum{NAME, TYPE, QUALIFIER, PARENS, BRACKETS};
char* qualifiers[] =    {"const", "volatile", "signed", "unsigned", "short", "long"};
char* datatypes[]  =    {"int", "double", "float", "char", "void"};

int is_datatype(char s[]);
int is_qualifer(char s[]);
void clear_output(void);
int gettoken(void); 
int getword(char*, int);
int getch(void);
void ungetch(int);
void obtain_output(char* out );
int tokentype;                  /* type of last token */
char token[MAXTOKEN];           /* last token string */
char out_master[MAXTOKEN];      /* output string */

/* Fun examples 
    x: function passing nothing returning pointer to array[] of pointer to char.                                                             
        - > char (*(*x())[])

    x: function passing int returning pointer to array[] of pointer to function passing nothing returning char.                                                         
        - > char (*(*x(int))[])()

    signal: function passing int and "fp", pointer to function passing int returning pointer to void, returning pointer to function passing int returning void.
         - > void (*signal(int, void* (*fp)(int)))(int)

    c: pointer to function passing "x", function passing nothing returning pointer to array[] of pointer to function passing nothing returning char, and "signal", function passing int and "fp", pointer to function passing int returning pointer to void, returning pointer to function passing int returning void, returning void.
         - > void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int))

    complex: pointer to function passing "com", pointer to function passing "x", function passing nothing returning pointer to array[] of pointer to function passing nothing returning char, returning void, and "signal", function passing int and "fp", pointer to function passing int returning pointer to void, returning pointer to function passing int returning void, returning void. 
        - > void (*complex)(void (*com)(char (*(*x())[])()), void (*signal(int, void *(*fp)(int)))(int))
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
            if (has_star){ /* this sets has_star in order to check for spurious parenthesis; they are only added if the following command is a bracket or parenthesis. */
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            }
            has_star = 1;
        }
        else if (type == NAME || type == TYPE || type == QUALIFIER){ /* unlike 5.20, separate qualifers for different strings are unnecessary. I'm keeping these here in case error handling is added later */
            if (has_star){
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
                    strcat(temp, ", ");
                }
                else 
                    strcat(temp, local_out);
                if (tokentype == ')') /* check for stopping criterion since obtain_output() changes tokentype */
                    break;
            }
            strcat(temp, ")");
            strcpy(local_out, temp); /* hold in case these arguments are for a function pointer.*/
            if (has_star){
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

/* gettoken: returns next token */
/* This is unlike previous gettoken functions. This one acts as an interpreter for getword and responds LIKE gettoken.*/
int gettoken(void)
{
    getword(token,MAXTOKEN);
    if (is_datatype(token) != -1)
        return tokentype = TYPE;
    else if (is_qualifer(token) != -1)
        return tokentype = QUALIFIER;
    else if (strcmp("function", token) == 0 ){
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
            for(int i = strlen(token) - 1 ; i >= 0; i--) /* store this for latter a function argument may be a complex declaration. */
                ungetch(token[i]);
            return tokentype = '(';
        }
    }
    else if (strcmp(token, "pointer") == 0){
        getword(token,MAXTOKEN);
        if (strcmp(token, "to") == 0)
            return '*';
        printf("ERROR: expected \"to\" to follow \"pointer\"\n");
        return -1;
    }
    else if (strcmp(token, "returning") == 0){
        if (tokentype == TYPE)
            return tokentype = ')';
        else
            gettoken(); /* call recursion whenever a complex declaration can be found, for this exercise this should only be return type and arrays  */
    }
    else if (strcmp(token, "and") == 0 )
        return tokentype  = ',';
    else if (strstr(token, "array[") != NULL){
        char* ptr = strstr(token, "[");
        int i = 0 ; 
        while (*ptr != '\0')
            token[i++] = *ptr++;
        token[i] = '\0';
        return BRACKETS;
    }
    else if (strcmp(token,"of") == 0){ /* only called after array[], could move this, yes, but this complicates logic */
        gettoken(); /* call recursion whenever a complex declaration can be found */
    }
    else if (strcmp(token, "\n") == 0)
        return tokentype = '\n';
    else{ /* NAME tokentype is the least safe option since it merely isn't anything else when parsing individual words. */
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
    if (c == '\n'){ /* this ensures each run is ended properly. */
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

/* resets variables for the next input */
void clear_output(void)
{
    tokentype = 0;
    token[0] = '\0';
    out_master[0] = '\0';
}
