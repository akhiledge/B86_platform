
/*
 * File:header.h
 * Author:Shrishail Satihal
 * Description:Rb tree insertion
 * Date:23-8-18
 * Last modified:23-8-18
 */



/*
 * header Guard
 */
#ifndef _HEADER_H

/*
 * Header Guard
 */
#define _HEADER_H

/*
 * @headerfile stdio.h
 */
#include<stdio.h>       

/*
 * @headerfile stdlib.h
 */
#include<stdlib.h>    

/*
 * @headerfile assert.h
 */
#include<assert.h>   

/*
 * @def MAX 50
 */
#define MAX 50

/*
 * @def RED 1
 */
#define RED 1       

/*
 * @def BLACK 0
 */
#define BLACK 0      

typedef struct tree{                                                                    
    int val;                                                                   
    char color:1;                                                               
    struct tree *left;                                                          
    struct tree *right;                                                         
    struct tree *parent;                                                        
}rbtree;                                                                              
/*
 * function prototype for insert operation
 * /
 rbtree *insert(rbtree *, int);       

/*
 * function prototype for creating a node
 */
rbtree *create(rbtree *, int);      

/*
 * function prototype for printing a node
 */
void print(rbtree *);     

/*
 * inorder traversal
 */
void inorder(rbtree *);

/*
 *function prototype for alternode
 */
rbtree *alternode(rbtree *, rbtree *);

/*
 * Function prototype for right rotating grand parent
 */
rbtree *right_rotategp(rbtree *, rbtree *); 

/*
 * Function prototype for left rotating grandparent
 */
rbtree *left_rotategp(rbtree *, rbtree *);   

/*
 *function prototype for right rotate
 */
void right_rotate(rbtree *);

/*
 * function prototype for left rotate
 */
void left_rotate(rbtree *);           
#endif ///end of header guard
