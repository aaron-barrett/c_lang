#include <stdio.h>

int main()
{
    void (*complex)(int, void (*signal(int, void (*fp)(int)))(int));
    void (*com)(char (*(*x())[])());
    void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int));
    void (**d)(int,int);
    void (**const d)(int,int); // Is this really valid?
    void (**de[5])(int,int);
    return 0;
}