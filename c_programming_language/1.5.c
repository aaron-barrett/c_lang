#include <stdio.h>

int main()
{
    int c ; 
    c = (getchar() != EOF);
    printf("c = %d\n",c);
    if (EOF == -1)
        printf("assholes");
}