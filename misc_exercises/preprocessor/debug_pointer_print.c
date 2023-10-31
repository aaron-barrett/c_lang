#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

// Ensures first if statement is called
#define DEBUG "DEFINED"

#ifdef DEBUG
#define REPORT_PTR_VALUE(v) printf("Pointer \"%s\" points to %p\n", #v, v)
#else 
#define REPORT_PTR_VALUE(v)
#endif

void func(const int* a_passed_to_func)
{
    REPORT_PTR_VALUE(a_passed_to_func);
}

int main()
{
    int a = 0 ; 
    func(&a);
    return 0;
}