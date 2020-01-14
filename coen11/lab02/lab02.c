/***************************
* lab02 -- coen11          *
* Gordon Reis -- 1/16/2019 *
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

// initialize global vars
char names[LENGTH][SIZE];
int size[SIZE];
int counter = 0;

// list function to print out up to counter 
int list(void) {
	// initialize var for loop
	int i;
	
	// check if names and size are empty
	if (counter == 0) {
		printf("%s", "The queue is empty\n");
		return 1;
	}
	
	// Print out party name and size
	printf("\n%-10s %s\n","Name:","Size:");
	for(i = 0; i < counter; i++) { 
		printf("%-10s", names[i]);
		printf("%2d\n", size[i]);
	}
	return 0;
}

// function to clear the entire queue to be empty
void clear(void) {
	int i;
	for(i = 0; i < SIZE; i++) {
		strcpy(names[i], "\0");
		size[i] = 0;
	}
	counter = 0;
}

// function to delete a single entry based on table size
int delete(int availability) {
	// initialize loop var
	int i;
	// set to -1 in case of no possibilities
	int pos = -1;
	
	// create new arrays to strcpy to global vars
	char new_names[LENGTH][SIZE];
	int new_size[SIZE];
	
	// check for available table
	for(i = 0; i < counter; i++) {
		if(size[i] <= availability)	{
			pos = i;
			break;
		}
	}
	
	// exit if nothing was available
	if(pos == -1) {
		printf("%s", "Table of this size unavailable to give to any party");
		return 1;
	}
	
	// copy all names/size up to available position
	for(i = 0; i < pos; i++) {
		strcpy(new_names[i], names[i]); 
		new_size[i] = size[i];
	}
	
	// copy all names/size after available position
	for(i = pos+1; i < SIZE+1; i++) {
		strcpy(new_names[i-1], names[i]);
		new_size[i-1] = size[i];
	}
	
	// copies local arrays to global arrays
	for(i = 0; i < SIZE; i++) {
		strcpy(names[i], new_names[i]);
		size[i] = new_size[i];
	}
	
	printf("%s", "Table removed");
	
	// decrement counter and return
	counter--;
	return 0;
}
// function to reserve a new table
int insert(char u_name[], int u_size) {
	
	// check if the queue is full
	if(counter > 9) {
		printf("%s", "The queue is full");
		return 1;
	}
	
	// check if table size given is over limit
	if(u_size > SIZE) {
		printf("%s", "That table size is too high");
		return 2;
	}
	
	// create local array for editting
	char new_names[LENGTH][SIZE];
	// for loop var initialization
	int i;
	
	// copy global array to local array
	for(i = 0; i < counter; i++) {
		strcpy(new_names[i], names[i]);
	}
	
	// add new reservation to local array
	strcpy(new_names[counter], u_name);
	
	// copy local array to global array
	for(i = 0; i < counter+1; i++) {
		strcpy(names[i],new_names[i]);
	}
	
	// set size directly to global size
	size[counter] = u_size;

	// increment counter and return
	counter++;
	return 0;
}
// main function
int main(void) {
	
	// initialize vars for user input and scan results
	int scan_result;
	char u_name[LENGTH];
	int u_size;
	
	// while loop to keep function running until user exits with break
	while(1==1) {
		
		// print options and scan result
		printf("%s", "\nPick a number\n1) List Queue\n2) Reserve Table\n3) Remove From Queue\n4) Clear Queue\n0) Exit\n\n");
		scanf("%d", &scan_result);
		
		// exit
		if(scan_result == 0) {
			break;
		}
		
		// print queue
		else if(scan_result == 1) {
			list();
		}
		
		// insert into queue
		else if(scan_result == 2) {
			printf("%s", "Type the name\n");
			scanf("%s", u_name);
			printf("%s", "Type the size\n");
			scanf("%d", &u_size);
			printf("Table %s created with size %d\n", u_name, u_size);
			insert(u_name, u_size);
		}
		
		// remove from queue
		else if(scan_result == 3) {
			printf("%s", "Enter the table size\n");
			scanf("%d", &u_size);
			delete(u_size);
		}
		
		// clear entire queue
		else if(scan_result == 4) {
			clear();
		}
	}
	return 0;
}


