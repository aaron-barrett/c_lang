/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   3.6: Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted
*   number must be padded with blanks on the left if necessary to make it wide enough.
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

void itoa(int n, char s[], int field_width)
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
    while (i < field_width)
        s[i++] = ' ';
    s[i++] = '\0';
    reverse(s);
}

int main()
{
    int field_width = 6;
    // int n = 521;
    // int n = -2147483647;
    int n = INT_MIN;
    char s[MAXLINE];
    itoa(n, s, field_width);
    printf("%d to string: %s\n",n, s);
    printf("Width of s: %d\n", strlen(s));
    return 0;
}
