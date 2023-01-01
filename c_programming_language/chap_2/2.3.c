#include <stdio.h>
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

int htoi(char s[]){
    int n = 0;
    int i = 0;
    int b = 1;
    int sign = 1;
    int bounds = strlen(s);
    if (s[0] == '-'){
        sign = -1;
        bounds--;
    }
    reverse(s);
    for(; i != bounds; i++){
        if (s[i] >= '0' && s[i] <= '9')
            n = n + (s[i] - '0')*b;
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = n + (s[i] - 'a' + 10)*b;
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = n + (s[i] - 'A' + 10)*b;
        else if (s[i] == 'x' || s[i] == 'X')
            i++;
        b = b*16;
    }
    n = sign*n;
    reverse(s);
    return n;
}

int main()
{
    char s[]  = "0x100";
    int n = htoi(s);
    // int n = -0x64;
    printf("%s in decimal is %d\n", s, n);
    return 0;
}