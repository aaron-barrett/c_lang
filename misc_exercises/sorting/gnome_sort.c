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

void gnome_sort(int* arr, int size )
{
    for(int i = 0 ; i != size ; )
        if (i == 0 || arr[i] >= arr[i-1])
            i++;
        else{
            swap(&arr[i], &arr[i-1]);
            i--;
        }
}


int main()
{
    int arr[] = {500, -1, -5, 3, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    gnome_sort(arr, size);
    print_arr(arr,size);
    if (sorted(arr,size) == -1)
        printf("NOT Sorted.\n");
    else 
        printf("Sorted!\n");
    return 0;
}
