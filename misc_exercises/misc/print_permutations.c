#include <stdlib.h>
#include <stdio.h>

int* gen_array(unsigned size){
    int* a = malloc(sizeof(int)*size);
    for(unsigned i = 0 ; i < size; i++)
        a[i] = i+1;
    return a;
}

void print_array(int* array, unsigned size){
    for(unsigned i = 0 ; i < size ; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_permutations(int* array, unsigned index, unsigned size, unsigned* count){
    if(index == size-1){
        print_array(array, size);
        (*count)++;
        return;
    }
    print_permutations(array, index+1, size, count);
    for(unsigned i = index+1; i < size; i++){
        swap(&array[index], &array[i]);
        print_permutations(array, index+1, size, count);
        swap(&array[index], &array[i]);
    }
}

int main(){
    unsigned size = 3;
    int* array = gen_array(size);
    printf("Array Before Permutations:\n");
    print_array(array,size);
    printf("\n");
    unsigned count = 0;
    print_permutations(array, 0, size, &count);
    printf("Number of Permutations %d\n", count);
    printf("\nArray After Permutations:\n");
    print_array(array,size);
    free(array);
    return 0;
}