#include <stdio.h>

int main(){
    // Becuase of floating point arithmetic, this operation fails by printing off 
    // an infinite string of negative numbers. 
    // This shows the danger of comparing different types.
    int b = -1 ;
    for(unsigned i = 0 ; i < b ; i++)
        printf("Here for %d\n", i);
    return 0;
}