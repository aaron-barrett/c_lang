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

// Note: If a=b, then the result is *a=*b=0 for *a=*b=/=0.
// Check for this.
void swap(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int partition(int* arr, int l, int r)
{
    int partition_index = l;
    for(int i = l ; i < r ; i++)
        if(arr[i] < arr[r])
            (i == partition_index) ? partition_index++ : swap(&arr[i], &arr[partition_index++]);
    if (r != partition_index)
        swap(&arr[r], &arr[partition_index]);
    return partition_index;
}

void quick_sort(int* arr, int l, int r) 
{
    if (r-l < 1)
        return;
    int m = partition(arr, l, r);
    quick_sort(arr, l, m-1);    
    quick_sort(arr, m+1, r);
}

int main()
{
    int arr[] = {-1, 500, -5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, size-1);
    print_arr(arr,size);
    if (sorted(arr,size) == -1)
        printf("NOT Sorted.\n");
    else 
        printf("Sorted!\n");
    return 0;
}