/**************************
* lab01 -- coen11         *
* Gordon Reis -- 1/9/2019 *
**************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// change the maximum value for the quotient/divisor
#define MAX_QUOTIENT_VALUE 10
#define MAX_DIVISOR_VALUE 10

int main (void) {
	// set random seed
	srand(time(0));
	
	// initialize vars
	int i;
	int correctAnswers = 0;
	int pct;
	
	// loop to ask user 10 times
	for (i = 0; i < 10; i++) {
		
		if (askUser() == 1) correctAnswers++;
	}
	
	// calculate percentage of correct answers
	pct = correctAnswers * 10;
	
	// print score
	printf("You scored a %d/10, a %d percent\n", correctAnswers, pct);
	
	// return for main func
	return 0;
}

int askUser() {
	
	// initialize vars
	int a,b,c;
	int userAnswer;
	
	// generate a,b,c as dividend, divisor, and quotient
	c = rand() % MAX_QUOTIENT_VALUE+1;
	b = (rand() % MAX_DIVISOR_VALUE) + 1;
	a = b*c;
	
	// print problem and ask user
	printf("%d / %d = ", a, b);
	scanf("%d", &userAnswer);
	
	// check answer and return correct or incorrect
	if ((userAnswer) == c) {
		printf("Correct\n\n");
		return 1;
	} else {
		printf("Incorrect, the correct answer was %d \n\n", c);
		return 0;
	}
	
}
