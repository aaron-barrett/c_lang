/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.5: Write a function any(s1,s2), which returns the first location in the string s1 where any character from s2 occurs, or -1 if s1
*   contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[])
{
    int index = -1;
    for(int k = 0 ; s2[k] != '\0'; k++)
        for(int i = 0 ; s1[i] != '\0'; i++)
            if (s1[i] == s2[k])
                if (i < index)
                    index = i;
    return index;
}

int main()
{
    char s1[] = "abcdeffg";
    char s2[] = "fge";
    int index = any(s1,s2);
    printf("\"%s\" has character from \"%s\" at lowest index %d which is character \'%c\'.\n",s1,s2,index,s1[index]);
    return 0;
}
