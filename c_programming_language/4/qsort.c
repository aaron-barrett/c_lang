#include <stdio.h>

void print(int* p, size_t n)
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ", p[i]);
    printf("\n");
}

void swap(int v[], int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int left, int right);

    if(left >= right)
        return ;
    swap(v, left, (left+right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

int main()
{
    int v[] = {2,3,1,-1,9,8,7};
    int n = sizeof(v) / sizeof(v[0]);
    print(v,n);
    qsort(v,0,n-1);
    print(v,n);
    return 0;
}