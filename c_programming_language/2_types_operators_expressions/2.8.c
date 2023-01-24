/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.8: Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions.
*   
*   Notes: Also included leftrot(x,n), the inverse, for the sake of completion.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAXLINE 1000
// #define INT_BITS 32

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(unsigned n, int b, char s[])
{
    if (b < 2 || b > 36){
        printf("Base is out of range for base: %d", b);
        return ;
    }
    int i,hold;
    i = 0 ; 
    do{
        if (b <= 10)
            s[i++] = n % b + '0';
        else {
            hold = n % b ;
            if (hold >= 10)
                s[i++] = (hold % 10) + 'A';
            else 
                s[i++] = hold + '0';
        }
    } while ((n /= b) > 0);
    s[i++] = '\0';
    reverse(s);
}

unsigned obtain_max_bits_of_int()
{
    int hold = INT_MAX;
    int count = 0;
    while(hold){
        count++;
        hold = hold << 1;
    }
    return count;
}

int rightrot(unsigned x, unsigned n)
{
    unsigned INT_BITS = obtain_max_bits_of_int();
    return ( x >> n) | (x << INT_BITS-n);
}

int leftrot(unsigned x, unsigned n)
{
    unsigned INT_BITS = obtain_max_bits_of_int();
    return (x << n) | (x >> INT_BITS - n);
}

int main()
{
    unsigned x = 0b1110111; // 0b not necessarily in the standard
    int n = 3;
    unsigned result = rightrot(x,n);
    char s1[MAXLINE];
    char s2[MAXLINE];
    itob(x, 2, s1);
    itob(result, 2, s2);
    printf("x = %s\tresult = %s\n",s1,s2);
    result = leftrot(result,n);
    itob(result, 2, s2);
    printf("x = %s\tresult = %s\n",s1,s2);
    return 0;
}
