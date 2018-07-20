/******
 * rb tree
 *******/ 
#ifndef _RB_TREE_H
#define _RB_TREE_H
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <stdbool.h> 
#include <string.h> 

#define BUF_SIZE 16
#define BLACK true
#define RED false
enum side {leftleft = 1, leftright, rightleft, rightright}; /*child position*/ 

typedef struct Node {
    int value;
    bool color;
    struct Node *left;
    struct Node *right;
} node;

int user_input (void);
int value_in_node (void);
void *allocate_memory (int size);
bool insert (int num);
bool inorder (node *subtree_root);
bool preorder (node *subtree_root);
bool postorder (node *subtree_root);
void balance (node *great_grandparent, node *grandparent, node *parent, enum side child_pos);
node *left_rotate (node *pivot);
node *right_rotate (node *pivot);
node *sibling (node *child, node *parent);

#endif 
