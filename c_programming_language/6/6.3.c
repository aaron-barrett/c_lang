#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100
#define MAXWORD 100

int match_count;
int line_number = 1;

struct tnode{
    char* word;
    int count;
    int line[MAXLINE];
    struct tnode* left;
    struct tnode* right;
};

struct tnode* addtree(struct tnode*, char*);
void treeprint(struct tnode*);
int getword(char*, int);

/* word frequency count */
int main(int argc, char* argv[])
{
    struct tnode* root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root,word);
    treeprint(root);
    return 0;
}

struct tnode* talloc(void);
char* strdup_(char*);

/* addtree: add a node with w, at or below p */
struct tnode* addtree(struct tnode* p, char* w)
{
    int cond = 0;
    if (p == NULL){             /*new word has arrived */
        p = talloc();           /* make a new node */
        p->word = strdup_(w);    /* stores the word somewhere safe*/
        p->count = 1;
        p->line[0] = line_number;
        p->left = p->right = NULL;
        return p;
    }
    else if ((cond = strcmp(w, p->word)) == 0){
        p->line[p->count] = line_number;
        p->count++;
    }
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else 
        p->right = addtree(p->right,w);
}

/* treeprint: in- order print of tree p*/
void treeprint(struct tnode* p)
{
    if(p != NULL){
        treeprint(p->left);
        printf("%4d \"%s\" on lines \n\t", p->count, p->word);
        printf("%d", p->line[0]);
        for(int i = 1 ; i < p->count ; i++)
            printf(", %d", p->line[i]);
        printf("\n");
        treeprint(p->right);
    }
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
    while (isspace(c = getch())){/* since this gets rid of white space, a new line will be stored in getch() for this call */
        if (c == '\n')
            line_number++;
    if (c == '\"'){ /* ignores strings */
        while ((c = getch()) != '\"')
        ;
        c = getch(); /* call getch after string detection */
    }
    if ( c == '/'){ /* ignores comments */
        c = getch(); /* check for additional '/' or '*' */
        if (c == '/') /* single line comment */
            while ((c = getch()) != '\n')
            ;
        if (c == '*') /* block comments */
            while ((c = getch()) != '/')
            ;
        c = getch(); /* call getch after comment detection */\
    }
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_'){ /* non alpha numeric characters and underscores cancel string.*/
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_'){ /* non alpha numeric characters and underscores cancel string. */
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
