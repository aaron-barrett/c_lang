#include <stdio.h>
#include <math.h>

#define SUM get_sum()

int get_sum()
{
	int ret = 0 ; 
	for (int i = 1 ; i < 10 ; i++)
		ret += pow(2, i);
	return ret;
}

void print_sudoku(int a[9][9])
{
	printf(" ");
	for (int k = 0 ; k < (3+4)*3+2 ; k++)
		printf("-");
	printf("\n");
	for (int i = 0 ; i < 9 ; i++)
	{
		for (int j = 0 ; j < 9; j++)
		{
			if (j % 3 == 0)
				printf("| ");
			printf("%d ", a[i][j]);
		}
		printf("|\n");
		if (i % 3 == 2)
		{
			printf(" ");
			for (int k = 0 ; k < (3+4)*3+2 ; k++)
				printf("-");
			printf("\n");
		}
	}
	printf("\n");
}

int check(int a[9][9])
{
	int col = 0; 
	int row = 0;
	for (int i = 0 ; i < 9 ; i++)
	{
		for (int j = 0 ; j < 9 ; j++)
		{
			row += pow(2, a[i][j]);
			col += pow(2, a[j][i]);
		}
		if (row != SUM || col != SUM)
			return -1;
		row = 0; 
		col = 0;
	}

	int block = 0; 
	for (int i = 0 ; i < 3 ; i++)
		for (int j = 0 ; j < 3 ; j++)
		{
			for (int ii = 0 ; ii < 3 ; ii++)
				for (int jj = 0 ; jj < 3 ; jj++)
					block += pow(2, a[i*3 + ii][j*3 + jj]);			
			if (block != SUM)
				return -1;
			block = 0;
		}

	return 0;
}

void find_zero(int a[9][9], int* ii, int *jj)
{
	for (int i = 0 ; i < 9 ; i++)
		for (int j = 0 ; j < 9 ; j++)
			if (a[i][j] == 0)
			{
				*ii = i;
				*jj = j;
				return;
			}
}

int check_entry(int a[9][9], int i, int j, int num)
{
	for (int k = 0 ; k < 0 ; k++)
		if (a[i][k] == num || a[k][j] == num)
				return -1;
	
	i = (i / 3) * 3;
	j = (j / 3) * 3;
	for (int ii = 0 ; ii < 3 ; ii++)
		for (int jj = 0 ; jj < 3 ; jj++)
			if (a[i + ii][j + jj] == num)
				return -1;
	
	return 0;
}

int solve(int a[9][9])
{
	int i = -1, j = -1;
	find_zero(a, &i, &j);
	if (i+j == -2 && check(a) == 0)
		return 0;

	for (int k = 0 ; k < 9 ; k++)
		if (check_entry(a, i, j, k) == 0)
		{
			a[i][j] = k;
			if(solve(a) == 0)
				return 0;
			else 
				a[i][j] = 0;
		}
	return -1;
}


int main()
{
	int a[9][9] = {
	{5, 3, 4, 6, 7, 8, 9, 1, 2},
	{6, 7, 2, 1, 9, 5, 3, 4, 8},
	{1, 9, 8, 3, 4, 2, 5, 6, 7},

	{8, 5, 9, 7, 0, 1, 4, 2, 3},
	{4, 2, 6, 8, 5, 3, 7, 9, 1},
	{7, 1, 3, 9, 2, 4, 8, 5, 6},

	{9, 6, 1, 5, 3, 7, 2, 8, 0},
	{2, 8, 7, 4, 1, 9, 6, 3, 5},
	{0, 4, 5, 2, 8, 6, 1, 7, 9}
	};

	if (solve(a) == 0)
		printf("Solved!\n");
	else 
		printf("NOT Solved!\n");
	print_sudoku(a);
	
	return 0;
}


// Solved Puzzle
// int a[9][9] = {
// {5, 3, 4, 6, 7, 8, 9, 1, 2},
// {6, 7, 2, 1, 9, 5, 3, 4, 8},
// {1, 9, 8, 3, 4, 2, 5, 6, 7},

// {8, 5, 9, 7, 6, 1, 4, 2, 3},
// {4, 2, 6, 8, 5, 3, 7, 9, 1},
// {7, 1, 3, 9, 2, 4, 8, 5, 6},

// {9, 6, 1, 5, 3, 7, 2, 8, 4},
// {2, 8, 7, 4, 1, 9, 6, 3, 5},
// {3, 4, 5, 2, 8, 6, 1, 7, 9}
// };