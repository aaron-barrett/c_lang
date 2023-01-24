/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.3: Write a pointer verion of the function strcat that we showed in Chapter 2: strcat(s,t) copies string t to the end of string s.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

#define ALLOCSIZE 10             /* size of available space */

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

void afree (char* p)                /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

void strcat_s(char* s, char* t)
{
    char* x = s;
    char* y = t;
    while (*++x != '\0');
    while ((*x++ = *y++) != '\0');
}

int main()
{
    
    char* s = alloc(5);
    *s = '1';
    *(s+1) = '2';
    *(s+2) = '\0'; 
    char* t = alloc(3);
    *t = '3';
    *(t+1) = '4';
    *(t+2) = '\0'; 
    printf("s = %s\n", s);
    printf("t = %s\n", t);

    printf("Full Buffer = ");
    for(int i = 0 ; i < ALLOCSIZE; i++)
        printf("%c ", allocbuf[i]);
    printf("\n");

    printf("s address = %d\n", s);
    printf("t address = %d\n", t);
    strcat_s(s,t);
    printf("s = %s\n", s);
    printf("t = %s\n", t);
    printf("s address = %d\n", s);
    printf("t address = %d\n", t);

    printf("Full Buffer = ");
    for(int i = 0 ; i < ALLOCSIZE; i++)
        printf("%c ", allocbuf[i]);
    printf("\n");
    return 0;
}
