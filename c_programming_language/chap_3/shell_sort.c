#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_int_array(int v[], int n){
    printf("%d ", v[0]);
    if(n != 1)
        for(int i = 1 ; i !=n; i++)
            printf("%d ", v[i]);
    printf("\n");
}

void randomize(int v[], int n){
    srand(time(NULL));
    int temp, index;
    for(int i = 0 ; i < n ; ++i){
        index = rand() % n;
        temp = v[index];
        v[index] = v[i];
        v[i] = temp;
    }
}

void shell_sort(int v[], int n){
    int gap, i, j, temp;
    for(gap = n/2 ; gap > 0; gap /= 2)
        for(i = gap; i < n ; i++)
            for(j = i - gap; j>=0 && v[j] > v[j+gap]; j-= gap){
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}

int main()
{
    int n = 10;
    // int v[] = {8,2,3,6,4,1,5,0,9,7};
    int v[n];
        for(int i = 0 ; i < n ; ++i)
            v[i] = i;
    randomize(v,n);
    print_int_array(v,n);
    shell_sort(v,n);
    print_int_array(v,n);
    return 0;
}