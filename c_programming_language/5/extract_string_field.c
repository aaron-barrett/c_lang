#include <stdio.h>
#include <string.h>
char* sorting_field = "chap";
char* next_sorting_field = "";

void determine_field(char* v1, char* v2, char s[], char t[]){
    char* s_start = strstr(v1,sorting_field);
    char* t_start = strstr(v2,sorting_field);
    if(s_start == NULL || t_start == NULL){
        s[0] = '\0';
        t[0] = '\0';
        printf("Field not for both\n");
        return;
    }
    if (next_sorting_field != "")
    {
        char* s_next = strstr(v1, next_sorting_field);
        char* t_next = strstr(v2, next_sorting_field);
        for(int i = 0 ; i < strlen(sorting_field); i++){
            s_start++;
            t_start++;
        }
        int i = 0;
        while(s_start < s_next)
            s[i++] = *s_start++;
        s[i] = '\0';
        i = 0;
        while(t_start < t_next)
            t[i++] = *t_start++;
        t[i] = '\0';
    }
    else {
        for(int i = 0 ; i < strlen(sorting_field); i++){
            s_start++;
            t_start++;
        }
        int i = 0;
        while (*s_start != '\0')
            s[i++] = *s_start++;
        s[i] = '\0';
        i = 0;
        while (*t_start != '\0')
            t[i++] = *t_start++;
        t[i] = '\0';
    }
}

int main()
{
   char* v1 = "chap1sec2";
   char* v2 = "1sec1";
   char s[100];
   char t[100];
   determine_field(v1,v2,s,t);
   printf("%s\n",s);
   printf("%s\n",t);
   

    return 0;
}
