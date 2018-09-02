/**
 * File              : ../header/rbt_header.h
 * Author            : Basava Prasad S J
 * Date              : 20.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */
/** @brief : Header file to implement red-black tree */

/**Header guards*/
#ifndef RBT_HEADER_H
#define RBT_HEADER_H

/**Header files*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio_ext.h>

/**Macro definitions*/
#define SUCCESS 1
#define FAIL 0
#define STR_SIZE 100

/**Enum declaration*/
enum selection {             /*to select operation to perform, traversal 
                               and color*/
    Insertion = 1,
    Deletion,
    Display,
    Pre_order = 1,
    Post_order,
    In_order,
    Black = 0,
    Red
};

/**Structure declaration for Tree node*/
struct node{ 
    struct node *parent;    /*to hold parent address*/
    char color;             /*color member*/
    int data;               /*data member*/
    struct node *rchild;    /*right child address*/
    struct node *lchild;    /*left child address*/
};
typedef struct node RBT_NODE;

/**Function declarations*/
RBT_NODE *create_node ();
RBT_NODE *insert_node (RBT_NODE *root);
RBT_NODE *insert_color (RBT_NODE *newnode, RBT_NODE *root);
/*RBT_NODE *delete_node (RBT_NODE *root);*/
RBT_NODE *rotate_right (RBT_NODE *grandparent, RBT_NODE *root);
RBT_NODE *rotate_left (RBT_NODE *grandparent, RBT_NODE *root);
RBT_NODE *rotate_right_left (RBT_NODE *parent_new, RBT_NODE *root);
RBT_NODE *rotate_left_right (RBT_NODE *parent_new, RBT_NODE *root);
void display_nodes (RBT_NODE *root);
void inorder_traversal (RBT_NODE *root);
void preorder_traversal (RBT_NODE *root);
void postorder_traversal (RBT_NODE *root);
/*int search_node (RBT_NODE *root);*/
int my_atoi (char *str);

/**End of header guards*/
#endif
