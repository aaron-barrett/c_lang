#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_sudoku(int** a, int r)
{
    int rsqrt = (int)sqrt(r);
    int width = (int)log10(r)+1;
	printf(" ");
	for (int k = 0 ; k < (width*rsqrt+rsqrt+1)*rsqrt+2 ; k++)
		printf("-");
	printf("\n");
	for (int i = 0 ; i < r ; i++)
	{
		for (int j = 0 ; j < r; j++)
		{
			if (j % rsqrt == 0)
				printf("| ");
			printf("%*d ", width, a[i][j]);
		}
		printf("|\n");
		if (i % rsqrt == (rsqrt-1))
		{
			printf(" ");
			for (int k = 0 ; k < (width*rsqrt+rsqrt+1)*rsqrt+2 ; k++)
				printf("-");
			printf("\n");
		}
	}
	printf("\n");
}

void free_sudoku(int** a, int r)
{
    for (int k = 0; k < r; k++)
        free(a[k]);
    free(a);
}

int** gen_blank_sudoku(int* r)
{
    int** a = malloc(sizeof(int*)* (*r));
    for (int i = 0 ; i < *r ; i++)
        a[i] = calloc(sizeof(int), (*r));
    return a;
}

int** read_in_sudoku(int*** a, int* r, int* c, char* filename)
{
    FILE* f;
    if ((f = fopen(filename, "r")) == NULL)
        exit(1);
    if (fscanf(f, "%d %d", r, c) != 2)
        exit(1);
    if (sqrt(*r) != sqrt(*c))
        exit(1);

    *a = gen_blank_sudoku(r);
    for (int i = 0; i < *r; i++)
        for (int j = 0; j < *r; j++)
            if (fscanf(f, "%d", &(*a)[i][j]) != 1)
                exit(1);
    fclose(f);
}

int main()
{
    char* filename = "solved_sudoku/sud2.txt";
    int** a = malloc(sizeof(int**));
    int r, c;
    read_in_sudoku(&a, &r, &c, filename);
    print_sudoku(a, r);
    free_sudoku(a, r);
    return 0;
}