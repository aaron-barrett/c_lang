/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.12: Extend entab and detab to accept the shorthand 
*   
*    entab -m +n

*   to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int entab(char line[], int max, int tabstop, int column_start);
int detab(char line[], int max, int tabstop, int column_start);
int getlines(char s[], int lim);

int main(int argc, char* argv[])
{
    char s[MAXLINE];
    long lineno = 0;
    int c;
    int TABSTOP = 8;
    int column = 8;
    int tab_mode = 1;
    while (argc > 1){
        argv++;
        argc--;
        c = *argv[0];
        switch(c){
            case '-':
                column = atoi(++argv[0]);
                break;
            case '+':
                TABSTOP = atoi(++argv[0]);
                break;
            case 'm':
                tab_mode = atoi(++argv[0]);
                break;
            default:
                argc = 0;
                break;
        }
    }
    switch(tab_mode){
        case 0 :
            printf("Enter a single line to entab:\n");
            entab(s,MAXLINE,TABSTOP,column);
            printf("%s\n",s);
            break;
        case 1:
            printf("Enter a single line to detab:\n");
            detab(s, MAXLINE, TABSTOP,column);
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

int detab(char s[], int lim, int TABSTOP, int column_start)
{
    int c, i,j;
    int tab_count = 0;
    int column_count = 0;

    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i){
        if (column_count < column_start){
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
        }
        else {
            if ( c == '\t'){
                tab_count = tab_count % TABSTOP;
                tab_count = TABSTOP - tab_count;
                column_count += tab_count;
            }
            else {
                column_count += 1;
            }
            s[i++] = c;
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

int entab(char s[], int lim, int TABSTOP, int column_start)
{
    int c, i;
    i = 0;
    int tab_count = 0;
    int space_count = 0;
    int column_count = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n'){
        if (column_count < column_start){
            if (c == ' ')
                ++space_count;
            else{
                if(space_count != 0){
                    tab_count = tab_count % TABSTOP;
                    if (space_count ==  TABSTOP - tab_count){
                        s[i++] = '\t';
                        column_count += TABSTOP - tab_count;
                    }
                    else{
                        column_count += space_count;
                        for(; space_count != 0; --space_count)
                            s[i++] = ' ';
                    }
                    space_count = 0;
                }
                ++tab_count;
                s[i++] = c;
            }
        }
        else {
            if (c == ' '){
                column_count++;
                space_count++;
            }
            else if (c == '\t')
            {
                tab_count = space_count % TABSTOP;
                column_count += TABSTOP - tab_count;
            }
            s[i++] = c;
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
