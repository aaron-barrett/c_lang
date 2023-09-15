#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

void dec_to_base(unsigned dec, unsigned base, char* bin){
	if (dec == 0)
		return;
	dec_to_base(dec / base, base, bin);
	char hold[MAX];
	sprintf(hold, "%d", dec % base);
	strcat(bin, hold);
}

int main(){
	char bin[MAX];
	bin[0] = '\0';
	unsigned dec = 10;
	unsigned base = 2;
	dec_to_base(dec, base, bin);
	printf("%d in base %d: %s\n", dec, base, bin);
	return 0;
}
