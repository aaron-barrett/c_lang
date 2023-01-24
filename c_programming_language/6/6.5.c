/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   6.5: Write a function undef that will remove a name and definition from the table maintained by lookup and install.
*   
*   Notes: This builds heavily from code in the text which is left uncommented. 
*********************************************************************************************************************************************/
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
void undef (char* name, char* defn);
char* strdup_(char*);


void print_hashtab(char* name[])
{
    for(int i = 0 ; i <  3 ; i++)
        for(struct nlist* np = hashtab[hash(name[i])]; np != NULL; np = np->next)
            printf("name = %s \t defn = %s\n", np->name, np->defn);
}


int main()
{
    char* name[] = {"#A", "#B", "#C"};
    char* defn[] = {"a", "b", "c"};
    for(int i = 0 ; i < sizeof(name) / sizeof(name[0]); i++)
        install(name[i], defn[i]);
    print_hashtab(name);
    undef(name[0], defn[0]);
    printf("hashtable after undef(%s, %s)\n", name[0], defn[0]);
    print_hashtab(name);
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
