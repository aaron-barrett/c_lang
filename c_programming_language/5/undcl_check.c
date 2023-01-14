#include <stdio.h>

int main()
{
    int func1 = 1;
    int* func2 = &func1;
    int (*(*funcp1)) = &func2;
    printf("Additional parenthesis: %d\n", **funcp1);
    int **funcp2 = &func2;
    printf("No additional parenthesis: %d\n", **funcp2);
    return 0;
}