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

void itob(int n, int b, char s[])
{
    if (b < 2 || b > 36){
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
    } while ((n /= b) > 0);
    if (sign == INT_MIN)
        s[0] = -(sign % b) % b + '0';
    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\0';
    reverse(s);
}

unsigned getbits(unsigned x, int p, int n)
{
    /* x = 0111 0111* /
    /* p = 4 , n = 3 */
    /* x >> (4-3+1)
        x >> 2 
        x = 0001 1101
    */
    /* ~0 = all 1's */
    /* ~0 << 3  = all 1's but 3 0's on the far right */
    /* ~(~0 << 3) = all 0's but 3 1's on the far right */
    /* 0001 1101 & ~(~0 << 3) = 101*/

    // x = (x >> (p-n+1));
    // int y =  (~(~0 << n));
    // return (x >> (p-n+1));
    // return (~(~0 << n));
    return (x >> (p-n+1)) & (~(~0 << n));
    // return x & y ;
}

int main()
{
    unsigned x = 0b01110111; // 0b not necessarily in the standard
    int p = 4;
    int n = 3;
    unsigned result = getbits(x,p,n);
    printf("%d from getbits(%d, %d, %d)\n", result, x, p, n);
    char s1[MAXLINE];
    char s2[MAXLINE];
    itob(x,2,s1);
    itob(result,2,s2);
    printf("In binary:\n%s\t%s\n", s1, s2);

    int y = 0177; // 127 in decimal, 0111 1111 in binary
    char s3[MAXLINE];
    itob(y, 2, s3);
    printf("%d in binary %s\n", y, s3);
    printf("%d = %d & 0177\n", (x & 0177), x);
    printf("%d = %d & ~0177\n", (x & ~0177), x);

    itob(y,1,s3);
    printf("%d in unary %s\n", y, s3);

    /* Ripped from https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm */
    unsigned int a = 60;	/* 60 = 0011 1100 */  
    unsigned int b = 13;	/* 13 = 0000 1101 */
    int c = 0;           

    c = a & b;       /* 12 = 0000 1100 */ 
    printf("Line 1 - Value of c is %d\n", c );

    c = a | b;       /* 61 = 0011 1101 */
    printf("Line 2 - Value of c is %d\n", c );

    c = a ^ b;       /* 49 = 0011 0001 */
    printf("Line 3 - Value of c is %d\n", c );

    c = ~a;          /*-61 = 1100 0011 */
    printf("Line 4 - Value of c is %d\n", c );

    c = a << 2;     /* 240 = 1111 0000 */
    printf("Line 5 - Value of c is %d\n", c );

    c = a >> 2;     /* 15 = 0000 1111 */
    printf("Line 6 - Value of c is %d\n", c );

    return 0;
}