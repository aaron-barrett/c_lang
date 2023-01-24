/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.4: Write an alternate version of squeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

void squeeze (char s1[], char s2[])
{
    int i, j, k;
    for(k = 0 ; s2[k] != '\0'; k++){
        for(i = j = 0 ; s1[i] != '\0'; i++)
            if (s1[i] != s2[k])
                s1[j++] = s1[i];
        s1[j] = '\0';
    }
}

int main()
{
    char s1[] = "abcdeffg";
    char s2[] = "aef";
    printf("Original input %s\n",s1);
    squeeze(s1,s2);
    printf("%s after removing all characters in %s\n",s1,s2);
    return 0;
}
