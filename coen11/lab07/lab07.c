/*****************************************
* lab07 -- coen11                        *
* Gordon Reis -- 2/13/2019               *
* Queue with a List Array using file I/O *
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// define node and list
typedef struct Entry {
	char name[20];
	int size;
	struct Entry* next;
		
} NODE;

typedef struct LIST {
    NODE* head;
    NODE* tail;
    NODE list[10];
} LIST;

// global vars
LIST queue[4];
FILE* fp;

// prototype functions
int main(int argc, char* argv[]);
int show(int max);
int list(void);
int delete(int availability);
int insert(char u_name[], int u_size);
int check_duplicate(char a[]);
int write_to_file(FILE* f);
void read_from_file(FILE* f);

// Print entries with size <= size n
int show(int max) {
	// initialize vars/points
	int i;
	NODE* p = queue[0].head;
	
	// check if names and size are empty
	if (queue[0].head == NULL && queue[1].head == NULL && queue[2].head == NULL && queue[3].head == NULL) {
		printf("%s", "The queue is empty\n");
		return 1;
	}
	
	//print p->size <= max
	printf("\n%-10s %s\n","Name:","Size:");
    for (i = 0; i < 4; i++) {
        p = queue[i].head;
        printf("List %d\n", i);
        while (p != NULL) {
            if(p->size <= max) {
                printf("%-10s", p->name);
                printf("%2d\n", p->size);
            }
            p = p->next;
        }
    }
	return 0;
	
	

}	


// list function to print out linked list 
int list(void) {
	
	// initialize vars/pointers
	int i;
	NODE* p = queue[0].head;
	
	// check if names and size are empty
    if (queue[0].head == NULL && queue[1].head == NULL && queue[2].head == NULL && queue[3].head == NULL) {
        printf("%s", "The queue is empty\n");
        return 1;
    }
	
	// Print out entry names and sizes
	printf("\n%-10s %s\n","Name:","Size:");
    for(i = 0; i < 4; i++) {
        p = queue[i].head;
        printf("List %d\n", i);
        while (p != NULL) {
            printf("%-10s", p->name);
            printf("%2d\n", p->size);
            p = p->next;
        }
    }
	return 0;
}

// function to delete a single entry from linked list based on table size
int delete(int availability) {
	// initialize loop var/node pointers
	int i = 0;
    int j = 0;
    NODE* p = NULL;
	NODE* q = NULL;
    
    int listnum;
    int list_to_check;
    
    if (availability < 3) {
        list_to_check = 1;
    } else if (availability < 5) {
        list_to_check = 2;
    } else if (availability < 7) {
        list_to_check = 3;
    } else {
        list_to_check = 4;
    }
    
	// set pos to -1 in case of no possibilities
	int pos = -1;
	
	// check for available table and set i to the position 
	// in the list of first available table
    for(i = 0; i < list_to_check; i++) {
        p = queue[i].head;
        j = 0;
        while(p != NULL) {
            if(p->size <= availability)	{
                listnum = i;
                pos = j;
                
                // break out of nested loops
                i = 5;
                break;
            }
            j++;
            p = p->next;
        }
	}
	
	// exit if nothing was available
	if(pos == -1) {
		printf("%s", "Table of this size unavailable to give to any party");
		return 1;
	}
	//reset p to correct listnum
	p = queue[listnum].head;
    
	// set p to position of prior to removed entry
	// and q to position of removed entry
	for(i = 0; i < pos-1; i++) {
		p = p->next;
	}
	q = p->next;
    
	
	// one item in list or 0 items in list
	if (queue[listnum].head == queue[listnum].tail && !(queue[listnum].head == NULL && queue[listnum].tail == NULL)) {
        queue[listnum].head = NULL;
        queue[listnum].tail = NULL;
        free(p);
    }
	// remove head
	else if (pos == 0) {
		free(p);
		queue[listnum].head = q;
	} 
	// remove tail
	else if (q == queue[listnum].tail) {
		queue[listnum].tail = p;
		queue[listnum].tail->next = NULL;
		free (q);
		if (queue[listnum].head == queue[listnum].tail) {
			queue[listnum].tail = NULL;
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
	// create node and fill with data
	NODE* insert = (NODE*)malloc(sizeof(NODE));
	
	strcpy(insert->name,u_name);
	insert->size = u_size;
	insert->next = NULL;
	
    int listnum;
    if(u_size < 3) {
        listnum = 0;
    } else if (u_size < 5) {
        listnum = 1;
    } else if (u_size < 7) {
        listnum = 2;
    } else {
        listnum = 3;
    }
	
	// insert node to list
	if(queue[listnum].head == NULL) {
		queue[listnum].head = insert;
		queue[listnum].tail = insert;
	}
	else {
		queue[listnum].tail->next = insert;
		queue[listnum].tail = insert;
	}

	// print and return	
	printf("Table %s created in list %d with size %d\n", u_name, listnum, u_size);
	return 0;
	
}
// checks the list of nodes for a duplicate node
// returns 1 if found, 0 if not found
int check_duplicate(char a[]) {
	
	int i;
	NODE* p = queue[0].head;
    for (i = 0; i < 4; i++) {
        while (p != NULL) {
            if(strcmp(p->name, a) == 0) {
                return 1;
            }
            p=p->next;
        }
        p = queue[i].head;
    }
	return 0;
}

// function to read lists from text files
void read_from_file(FILE* f) {
	// initialize variables
	char analyze[20];
	char u_name[20];
	int u_size;
	int counter = 0;
	
	// set seek_set after header
	fseek(f, 29, SEEK_SET);
	
	// scan in data
	while(fscanf(f, "%s", analyze) == 1) {
		if(counter % 2 == 0) {
			strcpy(u_name, analyze);
		} else { 
			u_size = atoi(analyze);
			insert(u_name, u_size);
		} 
		counter++;
	}
}

// function to write lists to text file
int write_to_file(FILE* f) {
	
	// initialize vars/pointers
	int i;
	NODE* p = queue[0].head;
	
	// check if names and size are empty
	if (queue[0].head == NULL && queue[1].head == NULL && queue[2].head == NULL && queue[3].head == NULL) {
		printf("%s", "The queue is empty\n");
		return -1;
	}
	
	// write names and sizes to files
	fprintf(f,"%s","Name      Size\n");
	fprintf(f,"%s","--------------\n");
	for(i = 0; i < 4; i++) {
		p = queue[i].head;
		while (p != NULL) {
			fprintf(f, "%s         %d\n", p->name, p->size);	
			p = p->next;
		}
	}
	return 1;
}

// main function to ask user which function to do
int main(int argc, char* argv[]) {
	
	// initialize vars for user input and scan results
	int scan_result;
	char u_name[20];
	int u_size;
	
	//read in file
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("%s","File not found");
	} else {
		read_from_file(fp);
	}
	
	// while loop to keep function running until user exits with break
	while(1==1) {
		
		// print options and scan result
		printf("%s", "\nPick a number\n1) Reserve Table\n2) Remove From Queue\n3) List Queue\n4) Show Queue up to size N\n5) Read from file\n6) Write to file\n0) Exit\n\n");
		scanf("%d", &scan_result);
		
		// exit
		if(scan_result == 0) {
			if ((fp = fopen(argv[1], "w")) == NULL) {
				printf("%s","File not found, not saving");
			} else {
				write_to_file(fp);
			}
            int i;
            NODE* p = NULL;
            NODE* q = NULL;
            for(i = 0; i < 4; i++) {
                p = queue[i].head;
                while (p != NULL) {
                    q = p;
                    p = p->next;
                    free(q);
                }
            }
            printf("%s","Lists freed\n");
			fclose(fp);
			printf("%s","File closed\n\n");
			printf("%s","Goodbye\n\n");
			break;
		}
		
		// insert into queue
		else if(scan_result == 1) {
			printf("%s", "Type the name\n");
			scanf("%s", u_name);
			printf("%s", "Type the size\n");
			scanf("%d", &u_size);
			insert(u_name, u_size);
		}
		
		// remove from queue
		else if(scan_result == 2) {
			printf("%s", "Enter the table size\n");
			scanf("%d", &u_size);
			delete(u_size);
		}
		
		// print queue
		else if(scan_result == 3) {
			list();
		}
		
		// show items for <= an int
		else if(scan_result == 4) {
			printf("%s", "Enter max table size\n");
			scanf("%d", &u_size);
			show(u_size);
		}
		// manual read from file
		else if(scan_result == 5) {
			if ((fp = fopen(argv[1], "r")) == NULL) {
				printf("%s","File not found");
			} else {
				read_from_file(fp);
			}
		}
		// manual print to file
		else if(scan_result == 6) {
			
			if ((fp = fopen(argv[1], "w")) == NULL) {
				printf("%s","File not found");
			} else {
				write_to_file(fp);
			}
			
		}
	}
	return 0;
}


