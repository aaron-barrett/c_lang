#include <stdlib.h>
#include <stdio.h>

unsigned trailing_zeros_fact(unsigned n){
	unsigned twos = 0;
	unsigned fives = 0;
	for(unsigned i = 1 ; i <= n ; i++){
		if (i % 2 == 0)
			twos++;
		if (i % 5 == 0)
			fives++;
	}
	return fives < twos ? fives : twos;
}


int main(){
	unsigned n = 16;
	unsigned trailing = trailing_zeros_fact(n);
	printf("%d! has %d trailing zeros.\n", n, trailing);
	return 0;
}
