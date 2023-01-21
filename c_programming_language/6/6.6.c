#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


struct nlist{               /* table entry */
    struct nlist * next;    /* next entry in chain */
    char* name;             /* defined name */
    char* defn;             /* replacement text */
};
#define HASHSIZE 101

static struct nlist* hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char* s);
struct nlist* lookup(char* s);
struct nlist* install(char* name, char* defn);
void undef (char* name, char* defn);
char* strdup_(char*);

#define MAXWORD 100


int main()
{
    int c, getch(void);
    void ungetch(int);
    char word[MAXWORD];
    word[0] = '\0';
    int word_count = 0;
    char name[MAXWORD];
    char defn[MAXWORD];
    char document[MAXWORD*MAXWORD];
    document[0] = '\0';
    int document_count = 0;
    struct nlist* np;
    while ((c = getch()) != EOF){
        printf("c = %c\n",c);
        document_count = strlen(document);
        while(!isalnum(c) && c != '#'){
            document[document_count++] = c;
            c = getch();
        }
        document[document_count] = '\0';
        while (isalnum(c) || c == '#'){
            word[word_count++] = c;
            c = getch();
        }
        word[word_count] = '\0';
        if (strcmp(word, "#define") == 0){
            strcat(document,word);
            document_count = strlen(document);
            word[0] = '\0';
            word_count=0;
            while(!isalnum(c)){
                document[document_count++] = c;
                c = getch();
            }
            document[document_count] = '\0';
            while (isalnum(c)){
                word[word_count++] = c;
                c = getch();
            }
            word[word_count] = '\0';
            strcat(document, word);
            strcpy(name, word);
            document_count = strlen(document);
            // document[document_count] = '\0';
            word[0] = '\0';
            word_count=0;
            while(!isalnum(c)){
                document[document_count++] = c;
                c = getch();
            }
            document[document_count] = '\0';
            while (isalnum(c)){
                word[word_count++] = c;
                c = getch();
            }
            word[word_count] = '\0';
            strcat(document, word);
            // document_count = strlen(document);
            // document[document_count++] = c;
            // document[document_count] = '\0';
            strcpy(defn, word);
            install(name, defn);
        }
        else if ((np = lookup(word) ) != NULL){
            strcat(document, np->defn);
            // ungetch(c);
            // document_count = strlen(document);
            // document[document_count++] = c;
            // document[document_count] = '\0';
        }
        else {
            strcat(document,word);
            // ungetch(c);
            // document_count = strlen(document);
            // document[document_count++] = c;
            // document[document_count] = '\0';
        }
        // ungetch(c);
        word[0] = '\0';
        word_count=0;
    }
    printf("%s\n", document);
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

/* undef: remove a name and definition in hashtab*/
void undef (char* name, char* defn)
{
    struct nlist *np;
    for(np = hashtab[hash(name)]; np!= NULL; np = np->next)
        if (strcmp(defn,np->defn) == 0)
            hashtab[hash(name)] = np->next;
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