/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   6.6: Implement a simple verison of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of 
*   this section. You may also find getch and ungetch helpful.
*   
*   Notes: Getch and ungetch were indeed helpful.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist{               /* table entry */
    struct nlist * next;    /* next entry in chain */
    char* name;             /* defined name */
    char* defn;             /* replacement text */
};

static struct nlist* hashtab[HASHSIZE]; /* pointer table */
unsigned hash(char* s);
struct nlist* lookup(char* s);
struct nlist* install(char* name, char* defn);
void undef (char* name, char* defn);
char* strdup_(char*);

enum{NAME, DEFINITION};

/* Possible example

#include <stdio.h>
#define VALUE 100
int array[VALUE];
int main()
{
    for(int i = 0 ; i<VALUE ; i ++)
        array[i] = VALUE * 500 - 34;
    return 0;
}

*/

int main()
{
    int c, type,  getch(void);
    void ungetch(int);
    char word[MAXWORD];
    int word_count = 0;
    char name[MAXWORD];
    char defn[MAXWORD];
    char document[MAXWORD*MAXWORD];
    document[0] = '\0';
    int document_count = 0;
    struct nlist* np;

    /* first call to ensure the main loop starts with an alphanumeric character or # */
    while ( !isalnum(c = getch()) && c != '#')
        document[document_count++] = c;
    document[document_count] = '\0';
    ungetch(c); /* avoids off by one error for the following loop */
    while ((c = getch()) != EOF){
        if ( !isalnum(c) && c != '#'){
            word[word_count] = '\0';
            if (strcmp(word, "") != 0){
                if (strcmp(word, "#define") == 0){
                    type = NAME;
                    strcat(document, word);
                }
                else if (type == NAME){
                    strcpy(name, word);
                    strcat(document, word);
                    type = DEFINITION;
                }
                else if (type == DEFINITION)
                {
                    strcat(document, word);
                    install(name, word);
                    type = -1;
                }
                else if (((np = lookup(word) ) != NULL)){
                    strcat(document, np->defn);
                    np = NULL;
                }
                else
                    strcat(document, word);
                word[0] = '\0'; /* reset word for next alpha numeric charcter string (including #)*/
                word_count = 0;
            }
            document_count = strlen(document);
            document[document_count++] = c;
        }
        else 
            word[word_count++] = c;
    }
    document[document_count] = '\0';
    printf("AFTER PREPROCESSING #DEFINE VALUES\n");
    printf("%s", document);
    return 0;
}


/* hash: form has value for string s*/
unsigned hash(char* s)
{
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist* lookup(char* s)
{
    struct nlist *np;
    for(np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s,np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found*/
}

/* install: put (name,defn) in hashtab */
struct nlist* install(char* name, char* defn)
{
    struct nlist* np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL){
        np = (struct nlist*) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup_(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else  /* already there */
        free ((void*) np->defn); /* free previous defn*/
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

char* strdup_(char* s)
{
    char* p;
    p = (char*) malloc(strlen(s)+1); /* +1 for '\0*/
    if (p != NULL)
        strcpy(p,s);
    return p;
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
