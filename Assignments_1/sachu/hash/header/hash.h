/**
 * @brief Header file with structure declaration and function prototypes
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <assert.h>

///Macro definitions
#define SIZE 20
#define MIN 0
#define MAX 1
#define INVALID -1

///Structure declaration
typedef struct info
{
    int word_count;        /*< word_count is an integer storing word count >*/
    char file_name[SIZE];  /*<file_name is a string storing name of file >*/
    struct info *down;     /*< down is a pointer storing down node address >*/
}detail;
typedef struct node
{
    char word[SIZE];       /*< word is a string storing word >*/
    int file_count;        /*< file_count is an integer storing file count >*/
    struct node *next;     /*< next is a pointer storing next node address >*/
    detail *down;          /*< down is a pointer storing down node address >*/
}hash;

//Function prototypes
int my_atoi(char *str);
int hash_index(char ch);
int search_word(hash **head, char *word);

void create_database(char *i_file, hash **table, char *temp);
void insert_first(hash **head, char *word, char *i_file);
void insert_sorted(hash **table, int key, char *temp, char *i_file);
void insert_last(hash **head, char *word, char *i_file);
void insert_before(hash **head, char *word, char *i_file);
void print_list(hash **head);
void search_database(hash **table, char *word);

hash *create_node(char *name, char *i_file);
detail *create_count(char *i_file);

void find_word(hash **head, char *word);
void save_data(hash **head, FILE *b_ptr);
void save_database(hash **table, char *b_file);
void update_database(char *b_file, hash **table);
void update_count(hash **head, char *temp, char *i_file);
void modify_string(char *str);
