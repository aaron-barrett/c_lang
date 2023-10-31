#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coord coord;
struct coord{
	int x ;
    int y;
};

#define DEF_PAIR_OF(dtype) \
  typedef struct pair_of_##dtype { \
       dtype first; \
       dtype second; \
  } pair_of_##dtype

 DEF_PAIR_OF(int);
 DEF_PAIR_OF(double);
 DEF_PAIR_OF(coord);

void print_centered_rectangle(pair_of_coord a)
{
    for(int i = 0 ; i < a.second.x - a.first.x ; i++)
        printf("- ");
    printf("\n");
    for(int j = 0 ; j < a.second.y - a.first.y; j++)
    {
        printf("- ");
        for(int i = 1 ; i < a.second.x - a.first.x -1 ; i++)
            printf("  ");
        printf("-\n");
    }
    for(int i = 0 ; i < a.second.x - a.first.x ; i++)
        printf("- ");
    printf("\n");
}


// the only reason this works for both ints and doubles is that any number can be 
// put into the print funcion 
#define PAIR_OF_PRINT(a, dtype) \
    if (strcmp(#dtype, "int") == 0 ) \
        printf("( %d, %d )\n", a.first, a.second); \
    else if (strcmp(#dtype, "double") == 0 )\
        printf("( %f, %f )\n", a.first, a.second);
    // Tempting, but this won't work
    // else if (strcmp(#dtype, "coord") == 0 )\
        // print_centered_rectangle(a);


 int main()
 {
    pair_of_int a; 
    a.first = 1;
    a.second = 2;
    PAIR_OF_PRINT(a, int);

    pair_of_double b;
    b.first = 1.0;
    b.second = 2.0;
    PAIR_OF_PRINT(b, double);

    // think rectangle abstraction
    // shows that a separate print is needed for more abstraction
    pair_of_coord c;
    c.first.x = 0;
    c.first.y = 0;
    c.second.x = 5;
    c.second.y = 6;
    print_centered_rectangle(c);
    
    return 0;
 }