#include <stdarg.h>
#include <stdio.h>
#include <string.h>


void concatenate_string(char* str, int ctr, ...){
    va_list args;
    va_start(args, ctr);
    for(int i = 0 ; i < ctr; i++)
        strcat(str,va_arg(args, char*));
    va_end(args);
}


int main(){
    char s[100] = "Strings ";
    concatenate_string(s, 2, "are ", "concatenated. ");
    printf("%s\n", s);
    return 0;
}