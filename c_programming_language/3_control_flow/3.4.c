/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   3.4: In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of 
*   of n equal to -(2^wordsize-1). Explain why not. Modify it to print that value corectly, regardless of the machine on which it runs.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXLINE 1000

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)
       if (sign == INT_MIN ){
            n++;
            n =- n;
       }
        else 
            n = -n;
    i = 0 ; 
    do{
        s[i++] = n % 10 + '0';
    } while ( (n /= 10) >0);
    if (sign == INT_MIN)
        s[0] = '8';
    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\0';
    reverse(s);
}

int main()
{
    int n = 521;
    // int n = -2147483647;
    // int n = INT_MIN;
    char s[MAXLINE];
    itoa(n,s);
    printf("%d to string: %s\n",n, s);
    return 0;
}
