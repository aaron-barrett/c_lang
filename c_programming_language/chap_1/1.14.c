#include <stdio.h>

int main()
{
    int c;
    int character_counter = '~' - ' ' + 1;
    int histogram_data[character_counter];
    for(int i = 0 ; i < character_counter ; ++i)
        histogram_data[i] = 0;
    while((c = getchar()) != EOF)
        histogram_data[c - 32]++;
    printf("\n");
    
    printf("(Horizontal Histogram)\n");
    printf("Word Length Frequency\n\n");
    for(int i = 0 ; i < character_counter ; ++i){
        if (histogram_data[i] != 0){
            printf("%c ", i + 32);
            for(int j = 0 ; j != histogram_data[i]; ++j)
                printf("-");
            printf("\n");
        }
    }
    printf("\n");

    printf("(Vertical Histogram)\n");
    printf("Word Length Frequency\n\n");
    int top = 0;
    for(int i = 0 ; i < character_counter ; ++i)
        if (histogram_data[i] > top)
            top = histogram_data[i];
    for(int j = top ; j > 0; --j){
        for(int i = 0 ; i < character_counter ; ++i)
            if (histogram_data[i] != 0){
                if (histogram_data[i] >= j)
                    printf("| ");
                else 
                    printf("  ");
            }
        printf("\n");
    }
    printf("\n");
    for(int i = 0 ; i < character_counter ; ++i)
        if (histogram_data[i] != 0)
            printf("%c ", i + 32);
    return 0;
}