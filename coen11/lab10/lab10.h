/*****************************************
* lab10 -- coen11 -- lab10.h             *
* Gordon Reis -- 3/13/2019               *
* lab10 header file                      *
*****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

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
extern LIST queue[4];
extern FILE* fp;
extern pthread_mutex_t mutex;
extern char* binary_name;

// prototype functions
int main(int argc, char* argv[]);
int show(int max);
int list(void);
int delete(int availability);
int insert(char u_name[], int u_size);
int check_duplicate(char a[]);
int write_to_file(FILE* f, int key);
void read_from_file(FILE* f, int key);
void delete_node(NODE* node);
void* save_loop(void* arg);
void write_to_binary(FILE* f);
void read_from_binary();