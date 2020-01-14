/*****************************************
* lab10 -- coen11                        *
* Gordon Reis -- 3/06/2019               *
* Thread save/load                       *
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "lab10.h"

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

// recursively free each nodes (call each head)
void delete_node(NODE* node) {
	if(node != NULL) {
		NODE* temp = node->next;
		free(node);
		delete_node(temp);
	}
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
