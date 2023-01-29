/*********************************************************************************************************************************************
*   Prints all primes between 1 and n, starting with a number line from 1 to 100 (really 2 to 100), and use a sieve method in a function to 
*   change the input array. Uses dynamic memory allocation within function, meaning we pass a pointer to a pointer of an integer array for the 
*   number line array and pointer to int, and change the input array using malloc() and free() and change the input size to the new size.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void create_sieve(int** sieve, int* size)
{
    int prime_count = 0;
    for (int i = 0 ; i < *size ; i++)
        if ((*sieve)[i] != 0){
            prime_count += 1;
            for(int j = i + (*sieve)[i] ; j < *size ; j += (*sieve)[i])
                (*sieve)[j] = 0;
        }
    int* s = (int*) malloc(prime_count * sizeof(int));  /* allocate memory of appropriate size*/
    int new_count = 0;
    for (int i = 0 ; i < *size ; i++)
        if ((*sieve)[i] != 0)
            s[new_count++] = (*sieve)[i];
    free(sieve);                                        /* free old memory*/
    (*sieve) = s;                                       /* set old pointer to new memory block */
    *size = prime_count;                                /* set old size to new size */
}

int main()
{
    int n = 100;
    int* sieve = (int*) malloc(n * sizeof(int)); /* initial number line */
    for(int i = 0 ; i < n ; i++)
        sieve[i] =  ( i > 0 ) ? i + 1 : 0; /* set 1 to  zero, for clarity */
    printf("Number Line: \t");
    for(int i = 0 ; i < n ; i++) /* print initial number line */
        printf("%d ", sieve[i]);
    printf("\n");
    create_sieve(&sieve, &n);
    printf("Primes: \t");
    for(int i = 0 ; i < n ; i++) /* print list of primes. */
        printf("%d ", sieve[i]);
    printf("\n");
    free(sieve);
    return 0;
}