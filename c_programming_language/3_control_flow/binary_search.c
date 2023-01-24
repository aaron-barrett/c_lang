#include <stdio.h>
#include <time.h>
#include <unistd.h>
int binary_search(int x, int v[], int n)
{
    int low, mid, high;
    low = 0 ; 
    high = n-1;
    while (low <= high){
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else 
            return mid;
    }
    return -1;
}

int main()
{
    int n = 10000;
    int arr[n];
    for(int i = 0 ; i != n; ++i)
        arr[i] = i;
    int find_value = 88920;
    clock_t begin = clock();
    int find_index = binary_search(find_value,arr,n);
    clock_t end = clock();
    float time = (double)(end-begin);
    printf("%d is at index %d\n", find_value, find_index);
    printf("Binary search took %f seconds to execute.\n", time);
    return 0;
}