#include <stdio.h>

void print_arr(int* arr, int size)
{
    for(int i = 0 ; i < size ; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int sorted(int* arr, int size)
{
    for(int i = 0 ; i < size -1; i++)
        if (arr[i] > arr[i+1])
            return -1;
    return 0;
}

// merges in place since we assume the two sorted sub arrays 
// that are consecutive in memory
void merge(int* a, int l, int m, int r)
{
    int hold, j;
    while(l < m && m < r)
        if (a[l] > a[m])
        {
            hold = a[m++];
            for(j = m-1 ; j > l ; j--)
                a[j] = a[j-1];
            a[l++] = hold;
        }
        else 
            l++;
}

void merge_sort(int* arr, int l, int r)
{
    if (r-l <= 1)
        return;
    int m = l + (r-l)/2;
    merge_sort(arr, l, m);
    merge_sort(arr, m, r);
    merge(arr, l, m, r);
}

int main()
{
    int arr[] = {500, -1, -5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    merge_sort(arr, 0, size);
    print_arr(arr,size);
    if (sorted(arr,size) == -1)
        printf("NOT Sorted.\n");
    else 
        printf("Sorted!\n");
    return 0;
}