#include <stdio.h>
#include <string.h>

int main()
{
    char a = 'B';
    if (a == 66)
        printf("assholes\n");
    printf("%c",a);
    a = 65;
    printf("%c",a);

    char b[] = "8letters";
    printf("%d\n", strlen(b));

    int min = 3; 
    int max = 6;
    if (min == 3)
        max = 7;
    else if (max == 7)
        min = 2;
    printf("min %d \t max %d\n", min , max);

    min = max++;
    printf("min = max++ result\n");
    printf("min %d \t max %d", min , max);
    return 0;
}