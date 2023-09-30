#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
			printf("%-*d ", width, a[i][j]);
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

void scrambled(int*** a, int r, double percent)
{
    int total_zeros = r*r*percent;
    int i, j;
    srand(time(0));
    for (int k = 0 ; k < total_zeros ; k++)
    {
        i = rand() % r;
        j = rand() % r;
        (*a)[i][j] = 0;
    }
}

void save_sudoku(int** a, int r, char* path)
{
    FILE* f;
    f = fopen(path, "w");
    fprintf(f, "%i %i\n", r, r);
    for(int i = 0 ; i < r ; i++)
    {
        for(int j = 0 ; j < r ; j++)
            fprintf(f, "%i ", a[i][j]);
        if (i != r-1)
            fprintf(f, "\n");
    }
    fclose(f);
}


int main()
{
    char filename[100] = "sud1.txt";
    char path[100];
    sprintf(path, "solved_sudoku/%s", filename);
    int** a = malloc(sizeof(int**));
    int r, c;
    read_in_sudoku(&a, &r, &c, path);

    double percent = 0.4;
    printf("Scrambled Sudoku with ~%0.f%% empty:\n", percent*100);
    scrambled(&a, r, percent);
    print_sudoku(a, r);

    filename[strlen(filename)-4] = '\0';
    sprintf(path,  "scrambled_sudoku/%s_per%0.1f.txt", filename, percent);
    save_sudoku(a, r, path);

    free_sudoku(a, r);
    return 0;
}