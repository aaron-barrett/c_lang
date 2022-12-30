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
    return 0;
}