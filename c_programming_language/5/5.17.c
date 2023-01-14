#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
char* lineptr[MAXLINES];
char* sorting_field = "";
char* next_sorting_field = "";

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort_(void* lineptr[], int left, int right, int (*comp)(void*, void*));
int numcmp(char*, char*);
int strcmp_(char*, char*);

int numeric = 0;
int reverse = 0;
int fold = 0;
int directory = 0;

void reset_options()
{
    numeric = 0;
    reverse = 0;
    fold = 0;
    directory = 0;
    sorting_field = "";
    next_sorting_field = "";
}

void print_operation()
{
    printf("sorting field \"%s\"\n", sorting_field);
    printf("next sorting field \"%s\"\n", next_sorting_field);
    printf("options ");
    if (numeric)
        printf("-n");
    if (reverse)
        printf("-r");
    if (fold)
        printf("-f");
    if (directory)
        printf("-d");
    printf("\n");
}

/* sort inputlies */
int main(int argc, char* argv[])
{
    int nlines = 0;
    int c;

    if ((nlines = readlines(lineptr, MAXLINES)) > MAXLINES){
        printf("input too big to sort\n");
        return 1;
    }
    else if (nlines == 0){
        printf("no input lines to sort\n");
        return 1;
    }
    /* initial sort to get those entries which have no overlapping sorting fields in their correct place.*/
    // qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*))(numeric ? numcmp : strcmp_));
    // writelines(lineptr, nlines);

    for(int i = 1 ; i < argc;){
        if (argv[i][0] != '-'){
            sorting_field = argv[i];
            i++;
        }
        if (i < argc)
            while (argv[i][0] == '-'){
                c = argv[i][1];
                i++;
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
                    case 'd':
                        directory = 1;
                    default:
                        break;
                }
                if (i >= argc)
                    break;
            }
        if (i < argc)
            next_sorting_field = argv[i];
        // print_operation();
        qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*))(numeric ? numcmp : strcmp_));
        reset_options();
    }
    writelines(lineptr, nlines);
    
    return 0;
}

/* qsort_: sort v[left]...v[right] into increasing order */
void qsort_(void* v[], int left, int right, int (*comp)(void*, void*))
{
    int i, last, to_swap;
    void swap(void* v[], int, int);
    void determine_field(char* v1, char* v2, char* s, char* t);
    if (left >= right)
        return ;
    last = left;
    for(i = left+1; i<= right; i++){
        if (sorting_field != ""){
            char s[100];
            char t[100];
            determine_field(v[i], v[left], s, t);
            if (s[0] != '\0' && t[0] != '\0'){
                if (reverse == 0){
                    if ((*comp)(s, t) < 0)
                        to_swap = 1;
                }
                else if (reverse == 1){
                    if ((*comp)(s, t) > 0)
                        to_swap = 1;
                }
            }
            // else {
            //     if (reverse == 0){
            //         if ((*comp)(sorting_field, next_sorting_field) < 0)
            //             to_swap = 1;
            //     }
            //     else if (reverse == 1){
            //         if ((*comp)(sorting_field, next_sorting_field) > 0)
            //             to_swap = 1;
            //     }
            // }
        }
        else{
            if (reverse == 0){
                if ((*comp)(v[i], v[left]) < 0)
                    to_swap = 1;
            }
            else if (reverse == 1){
                if ((*comp)(v[i], v[left]) > 0)
                    to_swap = 1;
            }
        }
        if (to_swap == 1)
            swap(v, ++last, i);
        to_swap = 0;
    }
    swap(v, left, last);
    qsort_(v, left, left-1, comp);
    qsort_(v, left+1, right, comp);
}

void determine_field(char* v1, char* v2, char s[], char t[]){
    char* s_start = strstr(v1,sorting_field);
    char* t_start = strstr(v2,sorting_field);
    if(s_start == NULL || t_start == NULL){
        s[0] = '\0';
        t[0] = '\0';
        return;
    }
    if (next_sorting_field != "")
    {
        char* s_next = strstr(v1, next_sorting_field);
        char* t_next = strstr(v2, next_sorting_field);
        for(int i = 0 ; i < strlen(sorting_field); i++){
            s_start++;
            t_start++;
        }
        int i = 0;
        while(s_start < s_next)
            s[i++] = *s_start++;
        s[i] = '\0';
        i = 0;
        while(t_start < t_next)
            t[i++] = *t_start++;
        t[i] = '\0';
    }
    else {
        for(int i = 0 ; i < strlen(sorting_field); i++){
            s_start++;
            t_start++;
        }
        int i = 0;
        while (*s_start != '\0')
            s[i++] = *s_start++;
        s[i] = '\0';
        i = 0;
        while (*t_start != '\0')
            t[i++] = *t_start++;
        t[i] = '\0';
    }
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
int compare_if_fold(char s, char t)
{
    if ( ((s <= 'z' && s >= 'a') || (s <= 'Z' && s >= 'A')) &&
     ((t <= 'z' && t >= 'a') || (t <= 'Z' && t >= 'A')) )
     return (tolower(s) == tolower(t));
    
}

int compare_if_directory(char s, char t)
{
    return (isalpha(s) || isdigit(s) || isspace(s)) && (isalpha(t) || isdigit(t) || isspace(t));
}

int to_skip(char s, char t)
{
    int skip = fold + directory;
    if (skip != 0){
        skip = 0;
        if (fold)
            skip += compare_if_fold(s, t);
        if (directory)
            skip += compare_if_directory(s,t);
    }
    return skip;
}

/* strcmp_: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_(char* s, char* t)
{
    int i;
    for(i = 0; s[i] == t[i] || to_skip(s[i], t[i]); i++)
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