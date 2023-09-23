/*********************************************************************************************************************************************
*   Prints all primes between 1 and n, starting with a number line from 1 to 100 (really 2 to 100), and use a sieve method in a function to 
*   change the input array. Uses dynamic memory allocation within function, meaning we pass a pointer to a pointer of an integer array for the 
*   number line array and pointer to int, and change the input array using malloc() and free() and change the input MAX to the new MAX.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void print_primes(int* sieve, int size)
{
    printf("Primes:");
    for(int i = 0 ; i < size ; i++)
    { 
        if (i % 10 == 0 )
            printf("\n");
        printf("%2d ", sieve[i]);
    }
    printf("\n");
}

int* create_sieve(int MAX, int* count)
{
    int* sieve = malloc(MAX * sizeof(int)); /* initial number line */
    for(int i = 0 ; i < MAX-1 ; i++)
        sieve[i] = i + 2 ;
    int prime_count = 0 ;
    for (int i = 0 ; i < MAX-1 ; i++)
        if (sieve[i] != 0)
        {
            prime_count += 1;
            for(int j = i + sieve[i] ; j < MAX ; j += sieve[i])
                sieve[j] = 0;
        }
    int* s = malloc(prime_count * sizeof(int));
    int new_count = 0;
    for (int i = 0 ; i < MAX -1 ; i++)
        if (sieve[i] != 0)
            s[new_count++] = sieve[i];
    free(sieve);
    sieve = s;
    *count = prime_count;
    return sieve;
}

int main()
{
    int MAX = 100;
    int n = 0;
    int* sieve = create_sieve(MAX, &n);
    print_primes(sieve, n);
    free(sieve);
    return 0;
}