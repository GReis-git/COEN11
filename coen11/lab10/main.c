/*****************************************
* lab10 -- coen11 -- main.c              *
* Gordon Reis -- 3/13/2019               *
* main function for lab10                *
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "lab10.h"

// global vars
LIST queue[4];
FILE* fp;
pthread_mutex_t mutex;
char* binary_name;

// main function to ask user which function to do
int main(int argc, char* argv[]) {
	
	// initialize vars for user input and scan results
	int scan_result;
	char u_name[20];
	int u_size;
	pthread_t pt;
	binary_name = argv[2];
	
	//read in file
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("%s %s","File not found, creating new file with name:", argv[1]);
	} else {
		read_from_file(fp, atoi(argv[3]));
	}
	
	// init thread for binary save loop
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&pt, NULL, save_loop, (void*) binary_name);
	
	// while loop to keep function running until user exits with break
	while(1==1) {
		
		// print options and scan result
		printf("%s", "\nPick a number\n1) Reserve Table\n2) Remove From Queue\n3) List Queue\n4) Show Queue up to size N\n5) Print Binary File\n0) Exit\n\n");
		scanf("%d", &scan_result);
		
		// exit
		if(scan_result == 0) {
			if ((fp = fopen(argv[1], "w")) == NULL) {
				printf("%s","File not found, not saving");
			} else {
				write_to_file(fp, atoi(argv[3]));
				printf("%s %s\n", "Saved to file", argv[1]);
			}
            int i;
            NODE* p = NULL;
            NODE* q = NULL;
            for(i = 0; i < 4; i++) {
                p = queue[i].head;
                delete_node(p);
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
		// 
		else if(scan_result == 5) {
			
            read_from_binary();
		}
		else {}
	}
	return 0;
}


