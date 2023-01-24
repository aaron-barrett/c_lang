/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   3.3: Write a function expand(s1,s2) that expands shorthand notation liek a-z in the string s1 into the equivalent complete list abc...xyz
*   in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading
*   or trailing - is taken literally.
*   
*   Notes: This implementation takes in consideration cases like "a-c-z", which are out of order, and cases like "a--B".
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main()
{
    char s1[] = "a-z";
    // char s1[] = "a-b-c";
    // char s1[] = "a-z0-9";
    // char s1[] = "-a-z";
    // char s1[] = "-a-z2-9";
    // char s1[] = "-Ba-w1-";
    // char s1[] = "a-c-b"; // tight corner check this case.
    // char s1[] = "-a-z-8"; // Really dumb case, should be aabcdefghijklmnopqrstuvwxyzz8
    // char s1[] = "a--B"; // Dumb Case
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
                if (hold_min >= '0' && hold_min <= '9')
                    hold_min = '0';
                else if (hold_min >= 'A' && hold_min <= 'Z')
                    hold_min = 'A';
                else if (hold_min >= 'a' && hold_min <= 'z')
                    hold_min = 'a';
                else 
                    printf("should not get here.\n");
            }
            else if (i != (strlen(s1)-1)){
                if (s1[i-1] == '-'){
                    hold_max = s1[i+1];
                    hold_min = -1;
                    if (hold_max >= '0' && hold_max <= '9')
                        hold_min = '0';
                    if (hold_max >= 'A' && hold_max <= 'Z')
                        hold_min = 'A';
                    if (hold_max >= 'a' && hold_max <= 'z')
                        hold_min = 'a';
                }
                else {
                    hold_max = s1[i+1];
                    hold_min = s1[i-1];
                    if (hold_min >= '0' && hold_min <= '9' && hold_max >= '0' && hold_max <= '9'){
                        if (hold_min > hold_max)
                            hold_max = '9';
                    }
                    else if (hold_min >= 'A' && hold_min <= 'Z' && hold_max >= 'A' && hold_max <= 'Z'){
                        if (hold_min > hold_max)
                            hold_max = 'Z';
                    }
                    else if (hold_min >= 'a' && hold_min <= 'z' && hold_max >= 'a' && hold_max <= 'z'){
                        if (hold_min > hold_max)
                            hold_max = 'z';
                    }
                    else {
                        if (hold_min >= '0' && hold_min <= '9')
                            hold_max = '9';
                        if (hold_min >= 'A' && hold_min <= 'Z')
                            hold_max = 'Z';
                        if (hold_min >= 'a' && hold_min <= 'z')
                            hold_max = 'z';
                    }
                }                    
            }
            else if (i == (strlen(s1)-1)){
                hold_min = s1[i-1];
                if (hold_min >= '0' && hold_min <= '9')
                    hold_max = '9';
                else if (hold_min >= 'A' && hold_min <= 'Z')
                    hold_max = 'Z';
                else if (hold_min >= 'a' && hold_min <= 'z')
                    hold_max = 'z';
                else 
                    printf("should not get here.\n");
            }
            while (hold_min <= hold_max)
                s2[j++] = hold_min++;
        }
        else{
            if (s1[i-1] == '-' && i > 0)
                continue;
            if (s1[i+1] == '-' && i < strlen(s1)-1)
                continue;
            s2[j++] = s1[i];
        }
    if (s2[j-1] != s1[i-1] && s1[i-1] != '-')
        s2[j++] = s1[i-1];
    s2[j] = '\0';
}
