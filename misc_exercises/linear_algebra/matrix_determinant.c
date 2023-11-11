#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack stack;
struct stack
{
	unsigned size ; 
	unsigned* data;
};

stack* stack_init()
{
	stack* a = malloc(sizeof(stack));
	a->size = 0;
	return a;
}

void free_stack(stack* a)
{
	if (a->size != 0)
		free(a->data);
	free(a);
}

void push(stack* a, unsigned new_data)
{
	if (a->size == UINT_MAX)
	{
		fprintf(stderr, "Error: Stack is full.\n");
		return ;
	}
	if (a->size == 0) 
	{
		a->data = malloc(sizeof(unsigned));
		a->data[0] = new_data;
	}
	else 
	{
		a->data = realloc(a->data, a->size);
		a->data[a->size]=new_data;
	}
	a->size++;
}

unsigned pop(stack* a)
{
	if (a->size == 0)
	{
		fprintf(stderr, "Error: Stack is empty.\n");
		return 0.0;
	}
	a->size--;
	unsigned ret = a->data[a->size];
	a->data = realloc(a->data, a->size);
	return ret;
}

int search(stack* a, unsigned item)
{
	for (unsigned i = 0 ; i < a->size; i ++)
		if (a->data[i] == item)
			return 1;
	return -1;
}

int srand_call = 0;

typedef struct matrix matrix;
struct matrix {
	double** mat;
	unsigned rows;
	unsigned cols;
};

void free_matrix(matrix* a)
{
	for (unsigned i = 0 ; i < a->rows; i++)
		free(a->mat[i]);
	free(a->mat);
	free(a);
}

matrix* matrix_init(unsigned rows, unsigned cols)
{
	matrix* a = malloc(sizeof(matrix));
	a->rows = rows;
	a->cols = cols;	
	a->mat = malloc(sizeof(double*) * rows);
	for (unsigned i = 0 ; i < rows; i++)
	{
		a->mat[i] = malloc(sizeof(double) * cols);
		for (unsigned j = 0 ; j < cols; j++)
			a->mat[i][j] = 0.0;
	}
	return a;
}

void print_matrix(matrix* a)
{
	for (unsigned i = 0 ; i < a->rows; i++)
	{
		for (unsigned j = 0; j < a->cols; j++)
			printf("%0.2f ", a->mat[i][j]);
		printf("\n");
	}
	printf("\n");
}

matrix* matrix_init_rand(unsigned rows, unsigned cols)
{
	if (srand_call == 0)
	{
		srand(time(NULL));
		srand_call = 1;
	}
	matrix* a = matrix_init(rows, cols);
	for (unsigned i = 0 ; i < rows ; i++)
		for ( unsigned j = 0 ; j < cols; j++)
			a->mat[i][j] = rand() % (rows * cols);
	return a;
}

// Uses the laplace expansion about the first row. 
// col_s keeps track of which rows have been "skipped" so far. 
// col_s + row_n explicitly tracks which subdeterminant(s) we are computing.
double determinant_laplace_computation(matrix* a, unsigned row_n, stack* col_s)
{
    if (a->rows - row_n == 1)
		for (int i = 0 ; i < a->cols; i++)
			if (search(col_s, i) == -1)
				return a->mat[row_n][i];

    double determinant = 0.0;
	// Since we are expanding about the first row, we need only the column count 
	// We expand about the first row of every submatrix, so restart count for every row.
	unsigned col_count = -1;
    for (int i = 0 ; i < a->cols; i++)
		if (search(col_s, i) == -1)
		{
			push(col_s,i);
			determinant += pow(-1, ++col_count) * a->mat[row_n][i] * determinant_laplace_computation(a, row_n+1, col_s);
			pop(col_s);
		}
    return determinant; 
}	

double determinant (matrix* a)
{
    assert(a->rows == a->cols);
	stack* col_s = stack_init();
	double det = determinant_laplace_computation(a, 0, col_s);
	free(col_s);
	return det;
}


int main()
{
	unsigned dim = 3; 
	matrix* a = matrix_init_rand(dim, dim);
    double det = determinant(a);
	printf("a = \n");
	print_matrix(a);
    printf("det(a) = %f", det);
	free_matrix(a);
	return 0;
}
