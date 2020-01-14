/***************************
* lab04 -- coen11          *
* Gordon Reis -- 1/30/2019 *
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

// define union
typedef union xinfo {
    char birthday_name[20];
    int years;
    float avg_age;
    
} XINFO;

// define struct
typedef struct entry {
	
	char name[20];
	int size;
    int special_occasion;
    XINFO extra_info;
	
} ENTRY;

// initialize entry array
ENTRY entries[SIZE];

// list to a max size, max
int show(int max) {
    
    // initialize vars
	int i;
	ENTRY* p = entries;
    
    // print
    printf("\n%-28s %-15s %9s\n","Name:","Size:","Special Occasion:");
	for(i = 0; i < counter; i++) { 
		if(p->size <= max) {
            printf("%-29s", p->name);
            printf("%-17d", p->size);
            
            int num = p->special_occasion;
            
            if(num==1) {
                printf("%-2s's Birthday\n", p->extra_info.birthday_name);
            }
            else if(num==2) {
                printf("%-2d Year Anniversary\n", p->extra_info.years);
            }
            else {
                printf("%-2f Average Age\n", p->extra_info.avg_age);
            }
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
    printf("\n%-23s %-15s %9s\n","Name:","Size:","Special Occasion:");
	for(i = 0; i < counter; i++) { 
		
        printf("%-24s", p->name);
		printf("%-17d", p->size);
        
        int num = p->special_occasion;
        
        if(num==1) {
            printf("%-3s's Birthday\n", p->extra_info.birthday_name);
        }
        else if(num==2) {
            printf("%-3d Year Anniversary\n", p->extra_info.years);
        }
        else {
            printf("%-3f Average Age\n", p->extra_info.avg_age);
        }
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
        p->special_occasion = (p+1)->special_occasion;
        int so = p->special_occasion;
        if (so == 1) {
            strcpy(p->extra_info.birthday_name, (p+1)->extra_info.birthday_name);
        } else if (so == 2) {
            p->extra_info.years = (p+1)->extra_info.years;
        } else {
            p->extra_info.avg_age = (p+1)->extra_info.avg_age;
        }
	}
	printf("%s", "Table removed");
	
	// decrement counter and return
	counter--;
	return 0;
}

// create a new entry
int insert(char u_name[], int u_size, int u_so, char u_bdayname[], int u_years, float u_avg_age) {
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
    entries[counter].special_occasion = u_so;
    if(u_so == 1) {
        strcpy(entries[counter].extra_info.birthday_name, u_bdayname);
    } else if (u_so == 2) {
        entries[counter].extra_info.years = u_years;
    } else {
        entries[counter].extra_info.avg_age = u_avg_age;
    }
    // increment counter, print, and return
    
    printf("Table %s created with size %d for occasion %d\n", u_name, u_size, u_so);
    counter++;
    return 0;
}

// local function used in insert to check for a duplicate
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
    int u_so;
    int u_years;
    float u_avg_age;
    char u_bdayname[LENGTH];
	
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
            printf("%s", "Is there any special occasion?\n 1) Birthday\n 2) Anniversary\n 3) No Occasion\n");
            scanf("%d", &u_so);
            if(u_so == 1) {
                printf("Enter birthday person's name\n");
                scanf("%s", u_bdayname);
            } else if(u_so == 2) {
                printf("Enter anniversary year\n");
                scanf("%d", &u_years);
            } else {
                printf("Enter average age\n");
                scanf("%f", &u_avg_age);
            }
            insert(u_name, u_size, u_so, u_bdayname, u_years, u_avg_age);
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


