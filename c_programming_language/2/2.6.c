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

int zero_out_inner_bits(unsigned x, int p, int n){
    return (x & (~0 << p+1)) | (x & (~(~0 << p-n+1)));
}

int setbits(unsigned x, int p, int n, unsigned y)
{
    y = ((y & (~((~0) << n))) << (p-n+1)) ;
    unsigned z = zero_out_inner_bits(x,p,n);
    return z | y;
}

int main()
{
    unsigned x = 0b1111101;// 0b not necessarily in the standard
    int p = 2; 
    int n = 2;
    unsigned y = 0b1110011;
    unsigned result = setbits(x,p,n,y);
    char s1[MAXLINE];
    char s2[MAXLINE];
    char s3[MAXLINE];
    itob(x, 2, s1);
    itob(y, 2, s2);
    itob(result, 2, s3);
    printf("x = %s\ty = %s \tresult = %s\n",s1,s2,s3);
    return 0;
}