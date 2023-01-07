#include <stdio.h>

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

void afree (char* p)                /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

int main()
{
    /* Shows the initial call.*/
    char* initial = NULL;
    int size = 10;
    initial = alloc(size);
    for(int i = 0 ; i != size; i++)
        initial[i] = i + '0';
    for(int i = 0 ; i != size; i++)
        printf("%c ", initial[i]);
    printf("\n");

    /* next call using the next consecutive memory blocks*/
    char* next = NULL;
    int next_size = 10; 
    next = alloc(next_size);
    for(int i = 0 ; i != size; i++)
        next[i] = i + '0';

    /* print showing that we can use the first pointer to access the memory allocated in next. */
    for(int i = 0 ; i != size + next_size; i++)
        printf("%c ", initial[i]);
    printf("\n");

    /* shows that the afree() changes frees the memory allocated with alloc, but that the memory still contains the same information.*/
    printf("%d\n", allocp);
    afree(next);
    printf("%d\n", allocp);
    for(int i = 0 ; i != size + next_size; i++)
        printf("%c ", initial[i]);
    printf("\n");

    return 0 ;
}