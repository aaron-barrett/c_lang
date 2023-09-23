#include <stdio.h>
#include <stdlib.h>

void print_grid(int** grid, int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
            printf("%2d  ", grid[i][j]);
        printf("\n\n");
    }
}

int** make_grid(int n)
{
    int** a = malloc(n * sizeof(int*));
    for (int i = 0 ; i < n ; i++)
        a[i] = malloc(n * sizeof(int));
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++)
            a[i][j] = -1;
    return a;
}

#define MOVECOUNT 8
int x[] = {-2, -1,  1,  2, 2, 1, -1, -2};
int y[] = {-1, -2, -2, -1, 1, 2, 2,   1};

int check_move(int n, int i, int j)
{
    if (i >= n || j >= n)
        return -1;
    if (i < 0 || j < 0)
        return -1;
    return 0;
}

int check_solve(int** a, int n, int i, int j)
{
    int count = 1;
    int old_count;
    while (count != n*n)
    {
        old_count = count;
        for (int k = 0 ; k < MOVECOUNT ; k++)
            if (check_move(n, i+x[k], j+y[k]) == 0 && 
                a[i+x[k]][j+y[k]] == count+1)
            {
                i += x[k];
                j += y[k];
                count++;
                break;
            }
        if (old_count == count)
         return -1;
    }
    return 0;
}

int solve(int** a, int n, int i, int j, int count)
{
    if (count == n*n)
        return 0;

    for (int k = 0 ; k < MOVECOUNT ; k++)
        if (check_move(n, i+x[k], j+y[k]) == 0 && 
            a[i+x[k]][j+y[k]] == -1)
        {
            a[i+x[k]][j+y[k]] = count+1;
            if (solve(a, n, i+x[k], j+y[k], count+1) == 0)
                return 0;
            else 
                a[i+x[k]][j+y[k]] = -1;
        }
    return -1;
}

int knights_tour(int** a, int n)
{
    int count = 1 ; 
    int i = 0, j = 0 ; 
    a[i][j] = count;
    return solve(a, n, i, j, count) == 0 ? check_solve(a, n, i, j) : -1;
}


int main()
{
    int n = 8;
    int** grid = make_grid(n);
    if (knights_tour(grid, n) == 0)
        printf("Solved!\n");
    else 
        printf("NOT Solved!\n");
    print_grid(grid, n);
    free(grid);
    return 0;
}