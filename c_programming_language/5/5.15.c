#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
char* lineptr[MAXLINES];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort_(void* lineptr[], int left, int right, int (*comp)(void*, void*));
int numcmp(char*, char*);
int strcmp_(char*, char*);

int numeric = 0;
int reverse = 0;
int fold = 0;

/* sort inputlies */
int main(int argc, char* argv[])
{
    int nlines;
    int c;
    while (argc > 1){
        argv++;
        argc--;
        c = *(++argv[0]);
        switch(c){
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                fold = 1;
                break;
            default:
                argc = 0;
                break;
        }
    }
    if (fold ==1)
        printf("fold\n");
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*))(numeric ? numcmp : strcmp_));
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsort_: sort v[left]...v[right] into increasing order */
void qsort_(void* v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    int to_swap = 0;
    void swap(void* v[], int, int);
    if (left >= right)
        return ;
    swap(v,left,(left+right)/2);
    last = left;
    for(i = left+1; i<= right; i++){
        if (reverse == 0){
            if ((*comp)(v[i], v[left]) < 0)
                to_swap = 1;
        }
        else if (reverse == 1){
            if ((*comp)(v[i], v[left]) > 0)
                to_swap = 1;
        }
        if (to_swap == 1)
            swap(v, ++last, i);
        to_swap = 0;
    }
    swap(v, left, last);
    qsort_(v, left, last-1, comp);
    qsort_(v, last+1, right, comp);
}

/* numcmp: compars s1 and s2 numerically */
/* strings without leading numbers are cast as 0.0 in atof() */
int numcmp(char* s1, char* s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else 
        return 0;
}

/* performs a comparison if fold option is chosen by comparing lower cases of relevant characters */
// int compare_if_fold(char s, char t)
// {
//     if ( ((s <= 'z' && s >= 'a') || (s <= 'Z' && s >= 'A')) &&
//      ((t <= 'z' && t >= 'a') || (t <= 'Z' && t >= 'A')) )
//      return (tolower(s) == tolower(t));
    
// }

/* strcmp_: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_(char* s, char* t)
{
    int i;
    if (fold == 1){
        for(i = 0; (tolower(s[i]) == tolower(t[i])) ; i++)
            if (s[i] == '\0')
                return 0;
        return tolower(s[i]) - tolower(t[i]);
    }
    else {
        for(i = 0; s[i] == t[i] ; i++)
            if (s[i] == '\0')
                return 0;
        return s[i] - t[i];
    }
}

void swap(void* v[], int i, int j)
{
    void* temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000 /* max length of any input line */
int getlines(char*, int);
char* alloc(int);
/* readlines: read input lines */
int readlines(char* lineptr[], int maxlines)
{
    int len, nlines;
    char* p, line[MAXLEN];
    nlines = 0;
    while ((len = getlines(line,MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char* lineptr[], int nlines)
{
    int i;
    for(i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int getlines(char s[], int lim)
{
    int c, i;

    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* defines the allcoation of lines.*/
#define ALLOCSIZE 1000             /* size of available space */

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char* allocp = allocbuf;      /* next free position */

char* alloc (int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n){ /* it fits */
        allocp += n;
        return allocp - n; /* old p*/
    }
    else 
        return 0;
}