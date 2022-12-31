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

void itob(int n, int b, char s[])
{
    if (b < 1 || b > 36){
        printf("Base is out of range for base: %d", b);
        return ;
    }
    int i, sign, hold;
    if ((sign = n) < 0){
       if (sign == INT_MIN ){
            n++;
            n =- n;
       }
        else 
            n = -n;
    }
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
    } while ( (n /= b) >0);
    if (sign == INT_MIN)
        s[0] = -(sign % b) % b + '0';
    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\0';
    reverse(s);
}

int main()
{
    int n = 5211;
    // int n = INT_MIN;
    int b = 11;
    char s[MAXLINE];
    itob(n, b, s);
    printf("%d to string in base %d: %s\n", n, b, s);
    return 0;
}