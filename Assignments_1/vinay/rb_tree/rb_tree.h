/**
 *\brief standard header files inclusion, function prototypes,global variables 
 **/ 
#ifndef _RB_TREE_H
#define _RB_TREE_H
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <stdbool.h> 
#include <string.h> 

#define BUF_SIZE 16                     /**< buffer size */ 
#define BLACK true                      /**< black color*/ 
#define RED false                       /**< red color*/ 

/**
 * \brief specify the insertion position of a new node to the tree with respest
 * to grandparent
 **/ 
enum side {
    leftleft = 1,
    leftright,
    rightleft,
    rightright
};

/**
 * \brief structure to store value in the tree
 **/ 
typedef struct Node {
    int value;                          /**< integer value stored in the node*/ 
    bool color;                         /**< color of the node*/ 
    struct Node *left;                  /**< pointer to left child*/ 
    struct Node *right;                 /**< pointer to right child*/ 
} node;                                 

int user_input (void);
int value_in_node (void);
void *allocate_memory (size_t size);
bool insert (int num);
bool inorder (node *subtree_root);
bool preorder (node *subtree_root);
bool postorder (node *subtree_root);
void balance (node *great_grandparent, node *grandparent, node *parent,\
        enum side child_pos);
node *left_rotate (node *pivot);
node *right_rotate (node *pivot);
node *sibling (node *child, node *parent);

#endif 
