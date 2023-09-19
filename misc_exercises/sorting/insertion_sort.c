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

void swap(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

// Jon Louis Bentley approach
void insertion_sort(int* arr, int size )
{
    for(int i = 1 ; i < size ; i++)
        for(int j = i ; j > 0 && arr[j-1] > arr[j] ; j--)
            swap(&arr[j], &arr[j-1]);
}


int main()
{
    int arr[] = {500, -1, -5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    insertion_sort(arr, size);
    print_arr(arr,size);
    if (sorted(arr,size) == -1)
        printf("NOT Sorted.\n");
    else 
        printf("Sorted!\n");
    return 0;
}