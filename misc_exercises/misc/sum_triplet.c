#include <stdlib.h>
#include <stdio.h>

void print_arr(int* arr, int size){
	for(int i = 0 ; i < size ; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void print_all_trip_sum_zero(int* arr, int size, int sum, int* trips){
		for(int i = 0 ; i < size ; i++)
			for(int j = i+1 ; j < size ; j++)
				for(int k = j+1 ; k < size ; k++)
					if (arr[i] + arr[j] + arr[k] == sum)
						printf("%d %d %d \n", i, j, k);
}


int main(){
	int arr[] = {-2, 0, 0, 1, 1, 1};
	int size = sizeof(arr) / sizeof(arr[0]);
	int trips[3];
	int sum = 0;
	printf("Array:\n");
	print_arr(arr, size);
	printf("Unique triplets that sum to %d:\n", sum);
	print_all_trip_sum_zero(arr, size, sum, trips);
	return 0;
}
