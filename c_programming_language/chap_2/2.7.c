#include <stdio.h>
#include <limits.h>
#include <string.h>

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

int invert(unsigned x, int p, int n)
{
    unsigned z = ((x >> (p-n+1)) & ~((~0 << n)));
    z = z << (p-n+1);
    z = ~z;
    unsigned y = (~(x >> (p-n+1)) & (~(~0 << n)));
    y = y << (p-n+1);
    x = x & z;
    x = x ^ y;
    return x;
}

int main()
{
    unsigned x = 0b1110111; // 0b not necessarily in the standard
    int p = 4; 
    int n = 3;
    unsigned result = invert(x,p,n);
    char s1[MAXLINE];
    char s2[MAXLINE];
    itob(x, 2, s1);
    itob(result, 2, s2);
    printf("x = %s\tresult = %s\n",s1,s2);
    return 0;
}