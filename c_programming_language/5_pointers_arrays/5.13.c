/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.13: Write the program tail, which prints the last n lines of its input. By default, n is 10, let us say, but it can be changed by an 
*   optional argument so that 
*
*   tail -n

*   prints the last n lines. The program should behave rationally not matter how unreasonable the input or value of n. Write the program so it 
*   makes the best use of the available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional
*   array of fixed size.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char* lineptr[MAXLINES];

int readlines(char* lineptr[], int nlines);
void write_tail(char* lineptr[], int nlines, int tail);

void qsort_(void* lineptr[], int left, int right, int (*comp)(void*, void*));
int strcmp_(char*, char*);

/* sort inputlies */
int main(int argc, char* argv[])
{
    int nlines,c;
    int tail = 10;
    while (argc > 1){
        argv++;
        argc--;
        c = *argv[0];
        switch(c){
            case '-':
                tail = atoi(++argv[0]);
                break;
            default:
                argc = 0;
                break;
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*))(strcmp_));
        write_tail(lineptr, nlines, tail);
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
    void swap(void* v[], int, int);
    if (left >= right)
        return ;
    last = left;
    for(i = left+1; i<= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_(v, left, left-1, comp);
    qsort_(v, left+1, right, comp);
}

/* strcmp_: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_(char* s, char* t)
{
    int i;
    for(i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
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

/* write_tail: write last tail (sorted) lines */
void write_tail(char* lineptr[], int nlines, int tail)
{
    int i; 
    i = (nlines < tail ) ?  0 : nlines - tail ;
    for(; i < nlines; i++)
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
