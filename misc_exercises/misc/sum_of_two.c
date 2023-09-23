#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int size)
{
	for(int i = 0 ; i < size ; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void sum_of_two(int* arr, int size, int sum, int indices[2])
{
	for(int i = 0 ; i < size ; i++)
		for(int j = i+1 ; j < size; j++)
			if(arr[i] + arr[j] == sum)
			{
				indices[0] = i;
				indices[1] = j;
				return;
			}
}

int main(){
	int arr[] = {4, 2, 1, 5};
	int size = sizeof(arr) / sizeof(arr[0]);
	int indices[2] = {-1,-1};
	int sum = 3;
	sum_of_two(arr, size, sum, indices);
	printf("Array: ");
	print_arr(arr, size);
	if(indices[0] + indices[1] == -2)
		printf("No pair of entries sums to %d.\n", sum);
	else
		printf("Entries %d and %d sums to %d.\n", indices[0], indices[1], sum);
	return 0;
}
