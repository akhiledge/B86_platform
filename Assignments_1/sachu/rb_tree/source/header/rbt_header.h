/*
   @brief Header file with structure definition and function prototypes
   */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <assert.h>

///Macro definitions
#define SIZE 5
#define RED 0
#define BLACK 1
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
bst_t *find_root(bst_t *root);
bst_t *create_node(bst_t *parent, int value);
bst_t  *left_rotate_from_gp(bst_t **parent);
bst_t *left_rotate_from_parent(bst_t **parent);
bst_t *right_rotate_from_gp(bst_t **parent);
bst_t *right_rotate_from_parent(bst_t **parent);

void insert_element(bst_t **root, int value);
void display_tree(bst_t *root);
void in_order(bst_t *root);
void pre_order(bst_t *root);
void post_order(bst_t *root);

bst_t *delete_element(bst_t *root);
bst_t *find_min_element(bst_t *root);
bst_t *delete_node_val(bst_t *root, int value);
bst_t *check_parent(bst_t **root, bst_t **parent, bst_t *child);
