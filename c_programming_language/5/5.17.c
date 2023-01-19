#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 /* max input lines */
#define MAXLEN 1000 /* max length of any input line */
char* lineptr[MAXLINES];
char sorting_field[100];
char next_sorting_field[100];
char past_sorting_field[100];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort_(void* lineptr[], int left, int right, int (*comp)(void*, void*,int,int));
int numcmp(char*, char*,int,int);
int strcmp_(char*, char*,int,int);

int numeric = 0;
int reverse = 0;
int fold = 0;
int directory = 0;
int numeric_past = 0;
int reverse_past = 0;
int fold_past = 0;
int directory_past = 0;

void reset_options()
{
    numeric_past = numeric;
    reverse_past = reverse;
    fold_past = fold;
    directory_past = directory;
    numeric = 0;
    reverse = 0;
    fold = 0;
    directory = 0;
}

void print_operation()
{
    printf("sorting field \"%s\"\n", sorting_field);
    printf("past sorting field \"%s\"\n", past_sorting_field);
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
    strcpy(next_sorting_field,"");
    strcpy(past_sorting_field,"");
    strcpy(sorting_field,"");

    if ((nlines = readlines(lineptr, MAXLINES)) > MAXLINES){
        printf("input too big to sort\n");
        return 1;
    }
    else if (nlines == 0){
        printf("no input lines to sort\n");
        return 1;
    }
    if (argc == 1){
        qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*,int,int))(numeric ? numcmp : strcmp_));
        writelines(lineptr, nlines);
        return 0;
    }
    for(int i = 1 ; i < argc;){
        if (argv[i][0] != '-'){
            strcpy(sorting_field,argv[i]);
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
            strcpy(next_sorting_field,argv[i]);
        else
            strcpy(next_sorting_field,"");
        qsort_((void**) lineptr, 0, nlines-1, (int(*)(void*, void*,int,int))(numeric ? numcmp : strcmp_));
        printf("After sort on field %s\n", sorting_field);
        writelines(lineptr, nlines);
        strcpy(past_sorting_field,sorting_field);
        reset_options();
    }
    // writelines(lineptr, nlines);
    
    return 0;
}

/* qsort_: sort v[left]...v[right] into increasing order */
void qsort_(void* v[], int left, int right, int (*comp)(void*, void*,int,int))
{
    int i, last;
    int to_swap = 0;
    void swap(void* v[], int, int);
    void determine_field(char* v1, char* v2, char* s, char* t, char* field, char* next_field);
    if (left >= right)
        return ;
    last = left; /* sets pivot element */
    char s[100];
    char t[100];
    for(i = left+1; i<= right; i++){
        if (strcmp(past_sorting_field, "") != 0){ /* checks that both elements are sorted according to past criterion */
            determine_field(v[i], v[left], s, t, past_sorting_field, sorting_field);
            if ((*comp)(s, t, fold_past, directory_past) != 0)
                continue;
        }
        determine_field(v[i], v[left], s, t, sorting_field, next_sorting_field);
        if (s[0] == '\0' || t[0] == '\0') /* checks that both elements contain the sorting element */
            continue;
        if (reverse == 0){
            if ((*comp)(s, t, fold, directory) < 0)
                to_swap = 1;
        }
        else if (reverse == 1){
            if ((*comp)(s, t, fold, directory) > 0)
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

void determine_field(char* v1, char* v2, char s[], char t[], char field[], char next_field[]){
    char* s_start = strstr(v1,field);
    char* t_start = strstr(v2,field);
    if(s_start == NULL || t_start == NULL){
        s[0] = '\0';
        t[0] = '\0';
        return;
    }
    if (strcmp(next_field, "") != 0)
    {
        char* s_next = strstr(v1, next_field);
        char* t_next = strstr(v2, next_field);
        for(int i = 0 ; i < strlen(field); i++){
            s_start++;
            t_start++;
        }
        if (s_next == NULL || t_next == NULL){
            int i = 0;
            while (*s_start != '\0')
                s[i++] = *s_start++;
            s[i] = '\0';
            i = 0;
            while (*t_start != '\0')
                t[i++] = *t_start++;
            t[i] = '\0';
        }
        else {
            int i = 0;
            while(s_start < s_next)
                s[i++] = *s_start++;
            s[i] = '\0';
            i = 0;
            while(t_start < t_next)
                t[i++] = *t_start++;
            t[i] = '\0';
        }
    }
    else {
        for(int i = 0 ; i < strlen(field); i++){
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
int numcmp(char* s1, char* s2, int fold, int directory)
{
    double v1, v2;
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);
    v1 = atof(s1);
    v2 = atof(s2);
    printf("v1 = %f\n", v1);
    printf("v2 = %f\n", v2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else 
        return 0;
}

void directory_filter(char *s)
{
    int k = 0;
    for(int i = 0 ; s[i] != '\0'; i++ )
        while ((isalnum(s[i]) == 0 && isspace(s[i]) == 0) && s[i] != '\0')
            for(k = i ; s[k] != '\0' ; k++)
                s[k] = s[k+1];
}

int strcmp_(char* s, char* t, int f, int d)
{
    int i;
    char ss[MAXLEN];
    char tt[MAXLEN];
    strcpy(ss,s);
    strcpy(tt,t);
    if (d == 1){
        directory_filter(ss);
        directory_filter(tt);
        printf("s = %s\n",ss);
        printf("ss = %s\n",ss);
        printf("t = %s\n",tt);
        printf("tt = %s\n",tt);
    }
    if (f == 1){
        for(i = 0; (tolower(ss[i]) == tolower(tt[i])) ; i++)
            if (ss[i] == '\0')
                return 0;
        return tolower(ss[i]) - tolower(tt[i]);
    }
    else {
        for(i = 0; ss[i] == tt[i] ; i++)
            if (ss[i] == '\0')
                return 0;
        return ss[i] - tt[i];
    }
}

void swap(void* v[], int i, int j)
{
    void* temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

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