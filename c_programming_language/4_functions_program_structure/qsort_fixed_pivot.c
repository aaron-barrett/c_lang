#include <stdio.h>

void print(int* p, size_t n)
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ", p[i]);
    printf("\n");
}

void qsort_fixed_pivot(int v[], int left, int right, int pivot_index)
{
    int i, last;
    void swap(int v[], int left, int right);
    if(left >= right)
        return ;
    int hold = pivot_index;
    while (right < hold + left)
        hold--;
    swap(v, left, left + hold);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_fixed_pivot(v, left, last-1, pivot_index);
    qsort_fixed_pivot(v, last+1, right, pivot_index);
}

void swap(int v[], int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main()
{
    int v[] = {2,3,1,-1,9,8,7};
    int n = sizeof(v) / sizeof(v[0]);
    print(v,n);
    int piv = 0;
    qsort_fixed_pivot(v,0,n-1,piv);
    print(v,n);
    return 0;
}