#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

char* strdup_(char*);


int main()
{
    char* name[] = {"#A", "#B", "#C"};
    char* defn[] = {"a", "b", "c"};
    for(int i = 0 ; i < sizeof(name) / sizeof(name[0]); i++)
        printf("hash(%s) = %d\n", name[i], hash(name[i]));
    for(int i = 0 ; i < sizeof(name) / sizeof(name[0]); i++)
        install(name[i], defn[i]);
    for(int i = 0 ; i < sizeof(name) / sizeof(name[0]); i++)
        for(struct nlist* np = hashtab[hash(name[i])]; np != NULL; np = np->next)
            printf("name = %s \t defn = %s\n", np->name, np->defn);
            
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