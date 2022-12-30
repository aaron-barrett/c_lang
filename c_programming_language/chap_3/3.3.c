#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "a-zass0-9";
    char s2[MAXLINE];
    printf("%s\n", s1);
    expand(s1,s2);
    printf("%s\n", s2);
    return 0;
}

void expand(char s1[], char s2[]){
    char hold_min;
    char hold_max;
    int i, j;
    i = j = 0;
    for(; i != strlen(s1); ++i)
        if (s1[i] == '-'){
            if (i == 0){
                hold_min = s1[i+1];
                hold_max = hold_min;
                if (hold_min >= 48 && hold_min <= 57)
                    hold_min = 48;
                else if (hold_min >= 65 && hold_min <= 90)
                    hold_min = 65;
                else if (hold_min >= 97 && hold_min <= 122)
                    hold_min = 97;
            }
            else if (i != strlen(s1)-1){
                hold_min = s1[i-1];
                hold_max = s1[i+1];
            }
            else if (i == strlen(s1)-1){
                hold_min = s1[i-1];
                if (hold_min >= 48 && hold_min <= 57)
                    hold_max = 57;
                else if (hold_min >= 65 && hold_min <= 90)
                    hold_max = 90;
                else if (hold_min >= 97 && hold_min <= 122)
                    hold_max = 122;
            }
            while (hold_min <= hold_max){
                s2[j] = hold_min;
                ++j;
                ++hold_min;
            }
        }
        else{
            if (s1[i-1] == '-' && i > 0)
                continue;
            if (s1[i+1] == '-' && i < strlen(s1)-1)
                continue;
            s2[j] = s1[i];
            ++j;
        }
    s2[j] = '\0';
}