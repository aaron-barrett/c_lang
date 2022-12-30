#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define NUMERIC_MIN 48
#define NUMERIC_MAX 57
#define UPPERCASE_MIN 65
#define UPPERCASE_MAX 90
#define LOWERCASE_MIN 97
#define LOWERCASE_MAX 122

void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "-b-Z";
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
                if (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX)
                    hold_min = NUMERIC_MIN;
                else if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX)
                    hold_min = UPPERCASE_MIN;
                else if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX)
                    hold_min = LOWERCASE_MIN;
            }
            else if (i != strlen(s1)-1){
                hold_min = s1[i-1];
                hold_max = s1[i+1];
                if      (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX && hold_max >= NUMERIC_MIN && hold_max <= NUMERIC_MAX){}
                else if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX && hold_max >= UPPERCASE_MIN && hold_max <= UPPERCASE_MAX){}
                else if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX && hold_max >= LOWERCASE_MIN && hold_max <= LOWERCASE_MAX){}
                else {
                    if (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX)
                        hold_max = NUMERIC_MAX;
                    else if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX)
                        hold_max = UPPERCASE_MAX;
                    else if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX)
                        hold_max = LOWERCASE_MAX;
                }
            }
            else if (i == strlen(s1)-1){
                hold_min = s1[i-1];
                if (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX)
                    hold_max = NUMERIC_MAX;
                else if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX)
                    hold_max = UPPERCASE_MAX;
                else if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX)
                    hold_max = LOWERCASE_MAX;
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