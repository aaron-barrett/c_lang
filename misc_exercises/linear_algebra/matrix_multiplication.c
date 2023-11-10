#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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
			printf("%f ", a->mat[i][j]);
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

matrix* matrix_multiplication(matrix* a, matrix* b)
{
	assert(a->cols == b->rows);
	matrix* c = matrix_init(a->rows, b->cols);
	for (unsigned i = 0 ; i < a->rows; i++)
		for (unsigned j = 0; j < b->cols; j++)
			for (unsigned k = 0 ; k < a->cols; k++)
				c->mat[i][j] += a->mat[i][k] * b->mat[k][j];
	return c;
}	


int main()
{
	unsigned rows_a = 2; 
	unsigned cols_a = 2;
	unsigned rows_b = 2;
	unsigned cols_b = 2;

	matrix* a = matrix_init_rand(rows_a, cols_a);
	matrix* b = matrix_init_rand(rows_b, cols_b);
	matrix* c = matrix_multiplication(a, b);

	printf("a = \n");
	print_matrix(a);
	printf("b = \n");
	print_matrix(b);
	printf("a*b = \n");
	print_matrix(c);

	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	return 0;
}
