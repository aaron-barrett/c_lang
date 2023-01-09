#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int entab(char line[], int max, int tabstop);
int detab(char line[], int max, int tabstop);

int main(int argc, char* argv[])
{
    int TABSTOP = atoi(argv[1]);
    return 0;
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