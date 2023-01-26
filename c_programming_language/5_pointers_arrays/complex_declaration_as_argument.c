#include <stdio.h>

struct complex{
    int a; 
    double b;
    float c;
};

int main()
{
    void (*complex)(int, void (*signal(int, void (*fp)(int)))(int));
    void (*com)(char (*(*x())[])());
    void (*c)(char (*(*x())[])(), void (*signal(int, void* (*fp)(int)))(int));
    void (**d)(int,int);
    void (*const e)(int,int);
    void (*volatile *const ef)(int,int); 
    void (**de[5])(int,int);
    struct complex (**func[5])(int,int);
    return 0;
}