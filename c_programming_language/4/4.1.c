#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 

int getlines(char line[], int max);
void reverse(char s[]);
int strindex(char source[], char searchfor[]);
char pattern[] = "ould";

int main()
{
    char line[MAXLINE];
    int found = 0;
    int index = 0;
    while(getlines(line, MAXLINE) > 0){
        if ((index = strindex(line, pattern)) >= 0){
            printf("%s", line);
            found++;
        }
        printf("Right most occurence of %s is at %d.\n",pattern,index);
    }
    return 0;
}

void reverse(char s[])
{
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int getlines(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim -1 > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[])
{
    reverse(s);
    reverse(t);
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++){
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0'){
            reverse(s);
            reverse(t);
            return (strlen(s) - strlen(t) - i);
        }
    }

    return -1;
}