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

// function to read lists from text files
void read_from_file(FILE* f, int key) {
	// initialize variables
    char analyze[200];
	char u_name[20];
	int u_size;
    int i = 0;
    char temp[20];
	
	// scan in data
	while(fgets(analyze, 200, f) != NULL) {
    
        for(i = 0; (analyze[i]^key) > 57; i++) {
			// create temp with the name of everything up to numbers
            temp[i] = analyze[i]^key;
        }
		insert(temp, analyze[i]^key-48);
		
		// LEGACY CODE
     //   strcpy(u_name, temp);
     //   u_size = analyze[i]^key-48;
        
     //   insert(u_name, u_size);
        /*
		if(counter % 2 == 0) {
			strcpy(u_name, analyze);
		} else { 
			u_size = atoi(analyze);
			insert(u_name, u_size);
        }
		counter++;
			END LEGACY
        */
	}
}

// function to write lists to text file
int write_to_file(FILE* f, int key) {
	
	// initialize vars/pointers
	int i,j;
    NODE* p;
    char buffer[200];
	// write names and sizes to files
	for(i = 0; i < 4; i++) {
		p = queue[i].head;
		while (p != NULL) {
            sprintf(buffer, "%s%d", p->name, p->size);
            for(j = 0; j < strlen(buffer); j++) {
                buffer[j] = buffer[j]^key;
            }
            fprintf(f, "%s\n", buffer);

			p = p->next;
		}
	}
	return 1;
}

// function to write a second file as a .bin
void write_to_binary(FILE* f) {
	NODE* p;
	int i;
	pthread_mutex_lock(&mutex);
	f = fopen(binary_name, "wb");
	
	
	for(i = 0; i < 4; i++) {
		p = queue[i].head;
		while (p != NULL) {
			
			// write buffer
			fwrite(p, sizeof(NODE), 1, f);
			
			//iterate
			p = p->next;
		}
	}
    fclose(f);
    pthread_mutex_unlock(&mutex);
}

// function to read and print from .bin
void read_from_binary() {
    NODE p;
	int i;
    pthread_mutex_lock(&mutex);
    FILE* f = fopen(binary_name, "rb");
    
	printf("\n%-10s %s\n","Name:","Size:");
    
    while(fread(&p, sizeof(NODE), 1, f) != 0) {
        printf("%-10s", p.name);
        printf("%2d\n", p.size);
    }
    fclose(f);
    pthread_mutex_unlock(&mutex);

}

// function to write to binary file every 15s
void* save_loop(void* arg) {
    while(1==1) {
        
        write_to_binary((FILE*) arg);
        
        printf("%s", "Autosave complete\n");
        sleep(15);
    }
}
