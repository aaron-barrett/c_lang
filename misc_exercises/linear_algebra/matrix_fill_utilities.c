#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

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

matrix* matrix_copy(matrix* a)
{
	matrix* b = matrix_init(a->rows, a->cols);
	for (unsigned i = 0 ; i < a->rows; i++)
		for (unsigned j = 0 ; j < a->cols; j++)
			b->mat[i][j]  = a->mat[i][j];	
	return b;
}

matrix* matrix_init_identity_multiple(unsigned rows, unsigned cols, double entry)
{
	matrix* a = malloc(sizeof(matrix));
	a->rows = rows;
	a->cols = cols;	
	a->mat = malloc(sizeof(double*) * rows);
	for (unsigned i = 0 ; i < rows; i++)
	{
		a->mat[i] = malloc(sizeof(double) * cols);
		for (unsigned j = 0 ; j < cols; j++)
            a->mat[i][j] = (i == j) ? entry : 0.0;
	}
	return a;
}

void matrix_fill_diagonal(matrix* a, int offset_diag, double entry)
{
	for (unsigned i = 0 ; i < fmin(a->rows, a->cols); i++)
		if (offset_diag >= 0)
			if (i+offset_diag < a->cols)
				a->mat[i][i+offset_diag] = entry;
			else 
				return;
		else if (offset_diag < 0)
			if (i - offset_diag < a->rows)
				a->mat[i - offset_diag][i] = entry;
			else 
				return ;
}

void matrix_fill_row(matrix* a, unsigned row, double entry)
{
    assert(row < a->rows && row >= 0);
    for (unsigned i = 0 ; i < a->cols; i++)
        a->mat[row][i] = entry;
}

void matrix_fill_col(matrix* a, unsigned col, double entry)
{
    assert(col < a->cols && col >= 0);
    for (unsigned i = 0 ; i < a->rows; i++)
        a->mat[i][col] = entry;
}

int main()
{
	unsigned rows_a = 4; 
	unsigned cols_a = 3;

	matrix* a = matrix_init(rows_a, cols_a);
	printf("a = \n");
	print_matrix(a);

	int fill_diag = 2; 
	double entry = 10.0;
	matrix_fill_diagonal(a, fill_diag, entry);
	printf("diag offset = %i \nfill value = %0.f\n", fill_diag, entry);
	printf("a = \n");
	print_matrix(a);

	fill_diag = -1;
	entry = -20.0;
	matrix_fill_diagonal(a, fill_diag, entry);
	printf("diag offset = %i \nfill value = %0.f\n", fill_diag, entry);
	printf("a = \n");
	print_matrix(a);

    entry = 5.0;
    unsigned fill_row = 0;
    matrix_fill_row(a, fill_row, entry);
    printf("fill row = %i \nfill value = %0.f\n", fill_row, entry);
    print_matrix(a); 

    entry = 6.0;
    unsigned fill_col = 1;
    matrix_fill_col(a, fill_col, entry);
    printf("fill col = %i \nfill value = %0.f\n", fill_col, entry);
    print_matrix(a); 

	free_matrix(a);
	return 0;
}
