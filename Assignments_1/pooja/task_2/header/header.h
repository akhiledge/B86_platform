///Header files inclusion

///Header guard
#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>	
#include<string.h>
#include<signal.h>
#include<stdlib.h>
#include<assert.h>

#define MAX 10						/**@def Macro for number of files*/
#define SIZE 200						/**@def Size of string*/
#define ARR_SIZE 50						/**@def Size of hashtable*/
///structure declaration
struct node{
	char *data;						///structure member for data of type character ptr
	int count[MAX];						///structure member for count
	char filename[MAX][SIZE]; 
	struct node *next;				///structure member for next node
};
typedef struct node NODE;		

enum choice {INSERT = 1, COPY, SEARCH, EXIT};
///function declarations
void insert(char *, char *, int);
int hash_func(char);
NODE *create_node(char *str);
void display(void);
void copy_file(FILE *, int);
int search(char *);
void display_node(NODE *);
void modify(char *);

extern NODE *hashtable[ARR_SIZE]; 
///End of header guard
#endif
