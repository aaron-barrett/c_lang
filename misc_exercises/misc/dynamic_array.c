#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct vector vector;
struct vector{
	unsigned size;
	int* data;
};

vector* vec_init()
{
	vector* a = malloc(sizeof(vector));
	a->data = calloc(sizeof(int), 1);
	a->size = 1;
	return a;
}

void print_vec(vector* a)
{
	for(unsigned i = 0 ; i < a->size; i++)
		printf("%d ", a->data[i]);
	printf("\n");
}

void push_back(vector* a, int new_data)
{
	a->size++;
	a->data = realloc(a->data, a->size * sizeof(int));
	a->data[a->size-1] = new_data;
}

int pop_back(vector* a)
{
	assert(a->size > 0);
	a->size--;
	int ret = a->data[a->size];
	a->data = realloc(a->data, a->size * sizeof(int));
	return ret;
}

void insert(vector* a, int new_data, unsigned index)
{
	assert(index <= a->size);
	if(index == a->size)
		push_back(a, new_data);
	else 
	{
		a->size++;
		a->data = realloc(a->data, a->size * sizeof(int));
		for (unsigned i = a->size-1; i > 0 ; i--)
			a->data[i] = a->data[i-1];
		a->data[index]=new_data;
	}
}


int main()
{
	vector* a = vec_init();
	push_back(a, 1);
	push_back(a, 2);
	printf("After two push_back:\n");
	print_vec(a);
	int new = 5;
	unsigned index = 1;
	insert(a, new, index);
	printf("After inserting %d at %d:\n", new, index);
	print_vec(a);
	int hold = pop_back(a);
	printf("After pop_back %d:\n", hold);
	print_vec(a);
	return 0;
}
