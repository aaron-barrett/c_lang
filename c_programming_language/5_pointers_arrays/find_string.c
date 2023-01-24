#include <stdio.h>
#include <string.h>

char* datatypes[] =  {"int", "double", "float", "char"};

int find_datatype(char s[]){
    for(int i = 0 ; i < sizeof(datatypes) / sizeof(datatypes[0]) ; i++)
        if (strcmp(s,datatypes[i]) == 0)
            return i;
    return -1;
}

int main()
{
    char s[] = "double";
    int index = -1;
    if((index = find_datatype(s)) != -1)
        printf("\"%s\" matches datatypes \"%s\"\n", s, datatypes[index]);
    else 
        printf("\"%s\" not found in datatypes \n", s);

    char t[] = "ints";
    if((index = find_datatype(t)) != -1)
        printf("\"%s\" matches datatypes \"%s\"\n", t, datatypes[index]);
    else 
        printf("\"%s\" not found in datatypes \n", t);

    return 0;
}