#include <stdio.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN 1000 /* max length of any input line */

char* lineptr[MAXLINES];

int readlines(char* lineptr[], char alloc[],  int maxlines);
void writelines(char* lineptr[], int nlines);

int main()
{
    int nlines; 
    char alloc[MAXLEN*MAXLINES];
    if ((nlines = readlines(lineptr, alloc, MAXLINES)) >= 0){
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too\n");
        return 1;
    }
}

int getlines(char*, int);
/* readlines: read input lines */
int readlines(char* lineptr[], char alloc[], int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    nlines = 0;
    int index = 0;
    while ((len = getlines(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            index += len;
            strcpy(&alloc[index], line);
            lineptr[nlines++] = &alloc[index];
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