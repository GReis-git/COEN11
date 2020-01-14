/***************************
* lab03 -- coen11          *
* Gordon Reis -- 1/23/2019 *
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

typedef struct entry {
	
	char name[20];
	int size;
	
} ENTRY;

ENTRY entries[SIZE];

int show(int max) {
	int i;
	ENTRY* p = entries;
	printf("\n%-10s %s\n","Name:","Size:");
	for(i = 0; i < counter; i++) { 
		if(p->size <= max) {
			printf("%-10s", p->name);
			printf("%2d\n", p->size);
		}
		p++;
	}
	return 0;
	
	

}	


// list function to print out up to counter 
int list(void) {
	
	// initialize vars/pointers
	int i;
	ENTRY* p = entries;
	
	// check if names and size are empty
	if (counter == 0) {
		printf("%s", "The queue is empty\n");
		return 1;
	}
	
	// Print out party name and size
	printf("\n%-10s %s\n","Name:","Size:");
	for(i = 0; i < counter; i++) { 
		printf("%-10s", p->name);
		printf("%2d\n", p->size);
		p++;
	}
	return 0;
}

// function to delete a single entry based on table size
int delete(int availability) {
	// initialize loop var/pointers
	int i;
	ENTRY* p = entries;
	// set to -1 in case of no possibilities
	int pos = -1;
	
	
	// check for available table
	for(i = 0; i < counter; i++,p++) {
		if(p->size <= availability)	{
			pos = i; 
			break; 
		}
	}
	
	// exit if nothing was available
	if(pos == -1) {
		printf("%s", "Table of this size unavailable to give to any party");
		return 1;
	}
	// move all items down in struct
	for(i = pos; i < SIZE; i++, p++) {
		strcpy(p->name, (p+1)->name);
		p->size = (p+1)->size;
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
		printf("%s", "The queue is full\n");
		return 1;
	}
	// check if duplicate
	if (check_duplicate(u_name) == 1) {
		printf("%s", "This name is already on the list\n");
		return 1;
	}
	
	// copy inserts into struct[counter]
	strcpy(entries[counter].name, u_name);
	entries[counter].size = u_size;
	
	// increment counter, print, and return
	
	printf("Table %s created with size %d\n", u_name, u_size);
	counter++;
	return 0;
	
}

int check_duplicate(char a[]) {
	
	int i;
	ENTRY* p = entries;
	
	for (i = 0; i < SIZE; i++, p++) {
		if(strcmp(p->name, a) == 0) {
			return 1;
		}
	}
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
		printf("%s", "\nPick a number\n1) List Queue\n2) Reserve Table\n3) Remove From Queue\n4) Show Queue up to size N\n0) Exit\n\n");
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
			insert(u_name, u_size);
		}
		
		// remove from queue
		else if(scan_result == 3) {
			printf("%s", "Enter the table size\n");
			scanf("%d", &u_size);
			delete(u_size);
		}
		
		// show items for <= an int
		else if(scan_result == 4) {
			printf("%s", "Enter max table size\n");
			scanf("%d", &u_size);
			show(u_size);
		}
	}
	return 0;
}


