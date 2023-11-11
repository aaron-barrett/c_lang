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

double trace (matrix* a)
{
    assert(a->rows == a->cols);
    double trace = 0.0;
    for(int i = 0 ; i < a->rows; i++)
        trace += a->mat[i][i];
    return trace;
}	


int main()
{
	unsigned rows_a = 2; 
	unsigned cols_a = 2;

	matrix* a = matrix_init_rand(rows_a, cols_a);
    double trace_a = trace(a);

	printf("a = \n");
	print_matrix(a);
    printf("Tr(a) = %f", trace_a);

	free_matrix(a);
	return 0;
}
