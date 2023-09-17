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

void bubble_sort(int* arr, int size )
{
    int move = 0;
    for(int i = 0 ; i < size - 1 ; i++)
    {
        move = 0;
        for(int j = 0 ; j < size - 1 - i ; j++)
            if (arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
                move = 1;
            }
        if (move == 0)
            break;
    }
}


int main()
{
    int arr[] = {500, -1, -5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, size);
    print_arr(arr,size);
    if (sorted(arr,size) == -1)
        printf("NOT Sorted.\n");
    else 
        printf("Sorted!\n");
    return 0;
}
