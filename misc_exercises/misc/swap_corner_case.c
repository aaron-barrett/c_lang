#include <stdio.h>
int main()
{
	int x = 10, y = 5;
	printf("Before Swapping: x = %d, y = %d\n", x, y);
	// Code to swap 'x' and 'y'
	x = x + y; // x now becomes 15
	y = x - y; // y becomes 10
	x = x - y; // x becomes 5
	printf("After Swapping: x = %d, y = %d\n", x, y);


    printf("Fails when swaping two pointers with the same address.\n");
    int z = 10;
	int* u = &z;
	int* v = &z;
    printf("Address u = %d and v = %d are the same as &z = %d\n", u, v, &z);
	printf("Before Swapping: *u = %d, *v = %d\n", *u, *v);
	*u = *u + *v; // *u=*v becomes 20
	*v = *u - *v; // *v=*u becomes 0
	*u = *u - *v; // *u=*v becomes 0
	printf("After Swapping: *u = %d, *v = %d\n", *u, *v);

	return 0;
}
