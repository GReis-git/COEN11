/***************************
* lab05 -- coen11          *
* Gordon Reis -- 2/06/2019 *
* Queue with a Linked List *
***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// define node
typedef struct Entry {
	char name[20];
	int size;
	struct Entry* next;
		
} NODE;

// global vars
NODE* head = NULL;
NODE* tail = NULL;

// Print entries with size <= size n
int show(int max) {
	// initialize vars/points
	int i;
	NODE* p = head;
	
	// check if names and size are empty
	if (p == NULL) {
		printf("%s", "The queue is empty\n");
		return 1;
	}
	
	//print p->size <= max
	printf("\n%-10s %s\n","Name:","Size:");
	while (p != NULL) { 
		if(p->size <= max) {
			printf("%-10s", p->name);
			printf("%2d\n", p->size);
		}
		p = p->next;
	}
	return 0;
	
	

}	


// list function to print out linked list 
int list(void) {
	
	// initialize vars/pointers
	int i;
	NODE* p = head;
	
	// check if names and size are empty
	if (p == NULL) {
		printf("%s", "The queue is empty\n");
		return 1;
	}
	
	// Print out entry names and sizes
	printf("\n%-10s %s\n","Name:","Size:");
	while (p != NULL) {
		printf("%-10s", p->name);
		printf("%2d\n", p->size);
		p = p->next;
	}
	return 0;
}

// function to delete a single entry from linked list based on table size
int delete(int availability) {
	// initialize loop var/node pointers
	int i = 0;
	NODE* p = head;
	NODE* q = NULL;
	
	// set pos to -1 in case of no possibilities
	int pos = -1;
	
	
	// check for available table and set i to the position 
	// in the list of first available table
	while(p != NULL) {
		if(p->size <= availability)	{
			pos = i; 
			break; 
		}
		i++;
		p = p->next;
	}
	
	// exit if nothing was available
	if(pos == -1) {
		printf("%s", "Table of this size unavailable to give to any party");
		return 1;
	}

	//reset p
	p = head;
	
	// set p to position of prior to removed entry
	// and q to position of removed entry
	for(i = 0; i < pos-1; i++) {
		p = p->next;
	}
	q = p->next;
	
	// one item in list, cannot be 0 items because of pos function
	if (head == tail) {
		head = NULL;
		tail = NULL;
		free(p);
	}

	// remove head
	else if (pos == 0) {
		free(p);
		head = q;
	} 
	// remove tail
	else if (q == tail) {
		tail = p;
		tail->next = NULL;
		free (q);
		if (head == tail) {
			tail = NULL;
		}
	}
	// set q to point to node after removed and free removed entry	
	else {
		p->next = q->next;
		free(q);
	}
	
	// print and return
	printf("%s", "Table removed");
	return 0;
}
// function to reserve a new table into the linked list
int insert(char u_name[], int u_size) {
	
	// check duplicate
	if (check_duplicate(u_name) == 1) {
		printf("%s", "This name is already on the list\n");
		return 1;
	}
	printf("%s", "Checked for dupe\n");
	// create node and fill with data
	NODE* insert = (NODE*)malloc(sizeof(NODE));
	printf("%s", "Mem allocated\n");
	strcpy(insert->name,u_name);
	insert->size = u_size;
	insert->next = NULL;
	printf("%s", "Data loaded\n");
	
	// insert node to list
	if(head == NULL) {
		head = insert;
		tail = insert;
		printf("%s", "First item inserted\n");
	}
	else {
		tail->next = insert;
		tail = insert;
		printf("%s", "entry inserted\n");
	}

	// print and return	
	printf("Table %s created with size %d\n", u_name, u_size);
	return 0;
	
}
// checks the list of nodes for a duplicate node
// returns 1 if found, 0 if not found
int check_duplicate(char a[]) {
	
	int i;
	NODE* p = head;
	while (p != NULL) {
		if(strcmp(p->name, a) == 0) {
			return 1;
		}
		p=p->next;
	}
	return 0;
}


// main function to ask user which function to do
int main(void) {
	
	// initialize vars for user input and scan results
	int scan_result;
	char u_name[20];
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


