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

int match_bits(unsigned x, int p, int n, unsigned y)
{
    x = zero_out_inner_bits(x,p,n);
    unsigned z = ~zero_out_inner_bits(~0,p,n);
    return x | (y & z);
}

int invert(unsigned x, int p, int n)
{
    unsigned y = zero_out_inner_bits(x,p,n);
    unsigned z = ~zero_out_inner_bits(~0,p,n);
    return y | ((~x) & z) ;
}

int main()
{
    unsigned x = 0b1110111;
    unsigned y = 0b110001;
    // unsigned x = 0b1110111; // 0b not necessarily in the standard
    int p = 4; 
    int n = 1;
    unsigned result = zero_out_inner_bits(x,p,n);
    char s1[MAXLINE];
    char s2[MAXLINE];
    itob(x, 2, s1);
    itob(result, 2, s2);
    printf("Zero out bits.\n");
    printf("x = %s\tresult = %s\n",s1,s2);
    result = match_bits(x,p,n,y);
    char s3[MAXLINE];
    itob(x, 2, s1);
    itob(y, 2, s2);
    itob(result,2,s3);
    printf("Match bits.\n");
    printf("x = %s\ty = %s\tresult = %s\n",s1,s2,s3);
    result = invert(x,p,n);
    itob(x, 2, s1);
    itob(result, 2, s2);
    printf("Invert bits.\n");
    printf("x = %s\tresult = %s\n",s1,s2);
    return 0;
}