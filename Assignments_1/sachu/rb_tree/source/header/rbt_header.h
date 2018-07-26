/**
 * @brief Header file with structure declaration and function prototypes
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <assert.h>

///Macro definitions
#define MIN 0
#define MAX 1
#define SIZE 10
#define RED 0
#define BLACK 1
#define INVALID -1
#define COLOR (root->color == 0)?("RED"):("BLACK")

///Strucure declaration
typedef struct bst
{
    struct bst *prev;  /*< prev is a pointer to store previous node address >*/
    int data;          /*< data is integer to store element >*/
    int color;         /*< color is integer to store node color>*/
    struct bst *left;  /*< left is a pointer to store left node address >*/
    struct bst *right; /*< right is a pointer to store right node address >*/
}bst_t;

///Function prototypes
int check_uncle(bst_t **parent);
int my_atoi(char *str);

bst_t *find_root(bst_t *root);
bst_t *create_node(bst_t *parent, int value);
bst_t  *left_rotate_from_gp(bst_t **parent);
bst_t *left_rotate_from_parent(bst_t **parent);
bst_t *right_rotate_from_gp(bst_t **parent);
bst_t *right_rotate_from_parent(bst_t **parent);
bst_t *search_element(bst_t *root, int value);
bst_t *find_min_element(bst_t *root);
bst_t *check_parent(bst_t **root, bst_t **parent, bst_t *child);

void insert_element(bst_t **root, int value);
void display_tree(bst_t *root);
void in_order(bst_t *root);
void pre_order(bst_t *root);
void post_order(bst_t *root);

void delete_element(bst_t **root);
void delete_node_value(bst_t **root, int value);
void operation_delete(bst_t **root, bst_t *d_node);
void double_black_fix(bst_t **d_node, bst_t **root);
void black_height_fix(bst_t **d_node, bst_t **root);
void search_tree(bst_t *root);
