/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   3.1: Our binary search makes two tests inside the loops, when one would suffice (at the price of more tests outside). Write a version with
*   only one test inside the loop and measure the difference in runtime.
*   
*   Notes: The last time I measured the difference in runtime, it was negligible, so I skip.
*********************************************************************************************************************************************/
#include <stdio.h>
#include <time.h>
int binary_search(int x, int v[], int n)
{
    int low, mid, high;
    low = 0; 
    high = n-1;
    while (low < high){
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else 
            low = mid+1;
    }
    if (v[low] == x)
        return low;
    else 
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
