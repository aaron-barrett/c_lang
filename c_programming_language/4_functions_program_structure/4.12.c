/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.12: Adapt the ideas of printd to write a recursive version of itoa; this is, convert an integer into a string by calling a recursive
*   routine.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa_recursion(int n, char s[], int i, int sign)
{
    if (n == 0){
        if (sign < 0){
            if (sign == INT_MIN)
                s[0] = '8';
            s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
        return ;
    }
    if (i == 0)
        if ((sign = n) < 0){
            if (sign == INT_MIN)
                n++;
            n = -n;
        }
    s[i++] = n % 10 + '0';
    n /= 10;
    itoa_recursion(n,s,i,sign);
}

void itoa(int n, char s[]){
    itoa_recursion(n,s,0,0);
    return ;
}

int main()
{
    int n = -5050;
    // int n = INT_MIN;
    char s[1000];
    itoa(n,s);
    printf("%d to string is %s.\n", n,s);
    return 0;
}
