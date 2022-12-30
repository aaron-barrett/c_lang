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
    // char s1[] = "a-c-b"; // tight corner check this case.
    // char s1[] = "a-b-c";
    // char s1[] = "-a-z";
    // char s1[] = "-a-z2-9";
    // char s1[] = "-a-z-8"; // Really dumb case, should be aabcdefghijklmnopqrstuvwxyzz8
    // char s1[] = "-Ba-w1-";
    // char s1[] = "a--B";
    // char s1[] = "a--B-"; // Really, really dumb case, should be abcdefghijklmnopqrstuvwxyzABBCDEFGHIJKLMNOPQRSTUVWXYZ

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
                else 
                    printf("should not get here.\n");
            }
            else if (i != strlen(s1)-1){
                if (s1[i-1] == '-'){
                    hold_max = s1[i+1];
                    hold_min = -1;
                    if (hold_max >= NUMERIC_MIN && hold_max <= NUMERIC_MAX)
                        hold_min = NUMERIC_MIN;
                    if (hold_max >= UPPERCASE_MIN && hold_max <= UPPERCASE_MAX)
                        hold_min = UPPERCASE_MIN;
                    if (hold_max >= LOWERCASE_MIN && hold_max <= LOWERCASE_MAX)
                        hold_min = LOWERCASE_MIN;
                }
                else {
                    hold_max = s1[i+1];
                    hold_min = s1[i-1];
                    printf("here' with hold_min %c\thold_max %c\n", hold_min, hold_max);
                    if (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX && hold_max >= NUMERIC_MIN && hold_max <= NUMERIC_MAX){
                        if (hold_min > hold_max)
                            hold_max = NUMERIC_MAX;
                    }
                    else if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX && hold_max >= UPPERCASE_MIN && hold_max <= UPPERCASE_MAX){
                        if (hold_min > hold_max)
                            hold_max = UPPERCASE_MAX;
                    }
                    else if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX && hold_max >= LOWERCASE_MIN && hold_max <= LOWERCASE_MAX){
                        if (hold_min > hold_max)
                            hold_max = LOWERCASE_MAX;
                    }
                    else {
                        if (hold_min >= NUMERIC_MIN && hold_min <= NUMERIC_MAX)
                            hold_max = NUMERIC_MAX;
                        if (hold_min >= UPPERCASE_MIN && hold_min <= UPPERCASE_MAX)
                            hold_max = UPPERCASE_MAX;
                        if (hold_min >= LOWERCASE_MIN && hold_min <= LOWERCASE_MAX)
                            hold_max = LOWERCASE_MAX;
                    }
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
                else 
                    printf("should not get here.\n");
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
    // printf("%s\n",s2);
    if (s2[j-1] != s1[i-1] && s1[i-1] != '-'){
        s2[j] = s1[i-1];
        ++j;
    }
    s2[j] = '\0';
}