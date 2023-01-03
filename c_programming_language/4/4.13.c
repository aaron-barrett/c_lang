#include <stdio.h>
#include <string.h>

void reverse(char s[], int i);

int main()
{
    char s[] = "Flip this String!";
    printf("%s\n",s);
    reverse(s,0);
    printf("%s\n",s);
    return 0;
}

void reverse(char s[], int i)
{
    if (i == strlen(s)/2)
     return ;
    else{
        char c = s[strlen(s)-1-i];
        s[strlen(s)-1-i] = s[i];
        s[i] = c;
        reverse(s,i+1);
    }
}