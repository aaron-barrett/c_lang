/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.11: Modify the programs entab and detab (written as exercises in Chapter 1) to accpet a list of tab stops as argument. Use the default 
*   tab settings if there are no arguments.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int entab(char line[], int max, int tabstop);
int detab(char line[], int max, int tabstop);
int getlines(char s[], int lim);

int main(int argc, char* argv[])
{
    int TABSTOP = 8;
    int tab_mode = 0;
    char s[MAXLINE];
    if (argc != 3){
        printf("Not enough arguments.\n");
        return 0;
    }
    else{
        TABSTOP = atoi(argv[1]);
        tab_mode = atoi(argv[2]);
    }
    switch(tab_mode){
        case 0 :
            printf("Enter a single line to entab:\n");
            entab(s,MAXLINE,TABSTOP);
            printf("%s\n",s);
            break;
        case 1:
            printf("Enter a single line to detab:\n");
            detab(s, MAXLINE, TABSTOP);
            printf("%s\n",s);
            break;
        default :
            printf("Invalid tab mode.\n");
            break;

    }
    return 0;
}

int getlines(char s[], int lim)
{
    int c, i;

    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int detab(char s[], int lim, int TABSTOP)
{
    int c, i,j;
    int tab_count = 0;
    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        if (c == '\t'){
            tab_count = tab_count % TABSTOP;
            tab_count = TABSTOP - tab_count;
            for(; tab_count != 0; --tab_count){
                s[i] = ' ';
                if (tab_count != 1)
                    ++i;
            }
        }
        else{
            ++tab_count;
            s[i] = c;
        }
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c=getchar()) != EOF && c != '\n')
            ++i;
    return i;
}

int entab(char s[], int lim, int TABSTOP)
{
    int c, i;
    i = 0;
    int tab_count = 0;
    int space_count = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n'){
        if (c == ' ')
            ++space_count;
        else{
            if(space_count != 0){
                tab_count = tab_count % TABSTOP;
                if (space_count ==  TABSTOP - tab_count){
                    s[i] = '\t';
                    ++i;
                }
                else 
                    for(; space_count != 0; --space_count){
                        s[i] = ' ';
                        ++i;
                    }
                space_count = 0;
            }
            ++tab_count;
            s[i] = c;
            ++i;
        }

    }
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c=getchar()) != EOF && c != '\n')
            ++i;
    return i;
}
