/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   6.4: Write a program that prints distinct words in its input sorted into decreasing order of frequency of occurence. Precede each word by
*   its word count.
*   
*   Notes: Unlike 6.2 and 6.3, this implementation disregards a binary tree as the container. This is to employ a quick sort on the frequency,
*   stored as "count", in tnode.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode{
    char* word;
    int count;
};
int node_count = 0;

void addnode(struct tnode*[], char*);
void qsort_(struct tnode* v[], int left, int right);
int getword(char*, int);

/* word frequency count */
int main()
{
    struct tnode* root[100];
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            addnode(root, word);
    qsort_(root, 0, node_count-1);
    for(int i = 0 ; i < node_count ; i++)
        printf("%d count for \"%s\"\n", root[i]->count, root[i]->word);
    return 0;
}

/* sort tnodes into decreasing order based on structure variable "count" */
void qsort_(struct tnode* v[], int left, int right)
{
    int i, last;
    void swap(struct tnode* v[], int left, int right);

    if(left >= right)
        return ;
    swap(v, left, (left+right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (v[i]->count > v[left]->count) /* sort in decreasing order here */
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_(v, left, last - 1);
    qsort_(v, last+1, right);
}

void swap(struct tnode* v[], int left, int right){
    struct tnode* temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

struct tnode* talloc(void);
char* strdup_(char*);

/* addnode: to word pointer array */
void addnode(struct tnode* p[],char* w)
{
    for (int i = 0 ; i < node_count; i ++) /* yes this is a linear search */
        if (strcmp(w, p[i]->word) == 0){
            p[i]->count++;
            return ;
        }
    p[node_count] = talloc();           /* make a new node */
    p[node_count]->word = strdup_(w);   /* stores word somewhere safe */
    p[node_count++]->count = 1;
    return ;
}


/*talloc: make a tnode */
struct tnode* talloc(void)
{
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char* strdup_(char* s)
{
    char* p;
    p = (char*) malloc(strlen(s)+1); /* +1 for '\0*/
    if (p != NULL)
        strcpy(p,s);
    return p;
}

/* getword: get next word or character from input */
int getword(char* word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char* w = word;
    while (isspace(c = getch()))
    ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)){
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())){
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
