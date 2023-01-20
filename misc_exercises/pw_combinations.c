#include <stdio.h>
#include <string.h>

#define MAXPW 52
#define MAXLENGTH 3

void obtain_pw(char save_pw[MAXPW][MAXLENGTH+1], char* pw, char* list, int list_index, int pw_index, int* count){
    if (*count == MAXPW)
        return;
    if (pw_index == MAXLENGTH){
        pw[pw_index] = '\0';
        strcpy(save_pw[*count], pw);
        (*count)++;
        return;
    }
    for(int i = list_index ; i < strlen(list) ; i++){
        pw[pw_index++] = list[i];
        obtain_pw(save_pw, pw, list, i, pw_index, count);
        --pw_index;
        if (*count == MAXPW)
            break;
    }
}

int main()
{
    char save_pw[MAXPW][MAXLENGTH+1];
    char pw[MAXLENGTH+1];
    char list[] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S' ,'s', 'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', '\0'};
    // char list[] = {'A', 'a', 'B', 'b', '\0'};
    int list_index = 0;
    int pw_index = 0;
    int out_count = 0;
    int* count ;
    count = &out_count;
    obtain_pw(save_pw, pw, list,list_index, pw_index,count);
    for(int i = 0 ; i < MAXPW; i++)
        printf("%s\n", save_pw[i]);
    return 0;
}