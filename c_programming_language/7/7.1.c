#include<stdio.h>
#include<string.h>
#include<ctype.h>

void input(int (*change_case)(int));

int main(int argc,char* argv[])
{
    if (argc == 1){
        printf("ERROR: input \"lower\" or \"upper\" to change case of input\n");
        return -1;

    }
    int c;
    int (*change_case)(int) = NULL;
    if (strcmp(argv[1],"lower")==0)
        change_case = tolower;
    else if (strcmp(argv[1],"upper")==0)
        change_case = toupper;
    input(change_case);
    return 0;
}

void input(int (*change_case)(int))
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(change_case(c));

}
