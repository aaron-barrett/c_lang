#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector vector;
struct vector{
	unsigned size;
	int* data;
};

vector* set_array()
{
    vector* a = malloc(sizeof(vector));
	a->data = calloc(sizeof(int), 1);
	a->size = 1;
    return a;
}

void free_vec(vector* a)
{
	free(a->data);
    free(a);
}

void print_vec(vector* a)
{
	for(unsigned i = 0 ; i < a->size; i++)
		printf("%d ", a->data[i]);
	printf("\n");
}

#define DEF_PAIR_OF(dtype) \
  typedef struct pair_of_##dtype { \
       dtype* first; \
       dtype* second; \
  } pair_of_##dtype

 DEF_PAIR_OF(vector);

void free_pair_of_vec(pair_of_vector a)
{
    free_vec(a.first);
    free_vec(a.second);
}

// TODO: try to generalize this for pointers to different arrays
// maybe via void pointers and casting
#define PAIR_OF_PRINT(a, dtype) \
    if (strcmp(#dtype, "vector") == 0 ) \
    {\
        print_vec(a.first); \
        print_vec(a.second); \
    }

 int main()
 {
    pair_of_vector c;
    c.first = set_array();
    c.second = set_array();
    PAIR_OF_PRINT(c, vector);
    free_pair_of_vec(c);
    return 0;
 }