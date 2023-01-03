#include <stdio.h>

int main()
{
    int c;
    int character_count = 0;
    int histogram_data[10];

    for(int i = 0 ; i < 10 ; ++i)
        histogram_data[i] = 0;

    while((c = getchar()) != EOF)
        if (c == ' ' || c == '\n' || c == '\t' || c == '.' || c == ','){
            if (character_count <= 9)
                ++histogram_data[character_count-1];
            else 
                ++histogram_data[9];
            character_count = 0;
        }
        else 
            ++character_count;

    printf("\n");
    printf("(Horizontal Histogram)\n");
    printf("Word Length Frequency\n\n");
    for(int i = 0 ; i < 10 ; ++i){
        if (i != 9)
            printf("%d ", i+1);
        else 
            printf(">9 ");
        for(int j = 0 ; j != histogram_data[i]; ++j)
            printf("-");
        printf("\n");
    }
    printf("\n");

    printf("(Vertical Histogram)\n");
    printf("Word Length Frequency\n\n");
    int top = 0;
    for(int i = 0 ; i < 10 ; ++i)
        if (histogram_data[i] > top)
            top = histogram_data[i];

    for(int j = top ; j > 0; --j){
        for(int i = 0 ; i < 10 ; ++i)
            if (histogram_data[i] >= j)
                printf("| ");
            else 
                printf("  ");
        printf("\n");
    }
    printf("\n");
    for(int i = 0 ; i < 10 ; ++i)
        if (i != 9)
            printf("%d ", i+1);
        else 
            printf(">9");
    return 0;
}