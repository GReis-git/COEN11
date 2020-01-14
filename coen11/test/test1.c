/**************************
* lab01 -- coen11         *
* Gordon Reis -- 1/9/2019 *
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (void) {
	srand(time(0));
	int *p;
	
	p = generateRand();
	
	for (int i = 0; i < 2; i++) {
		printf("%d\n", *p);
	}
}

int * generateRand() {
	
	int vars[2];
	for(int i = 0; i < 2; i++) {
		vars[i] = rand();
	}
	return vars;
}	