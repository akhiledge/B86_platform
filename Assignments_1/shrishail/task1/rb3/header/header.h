#include<stdio.h>                                                               
#include<stdlib.h>                                                              
#include<assert.h>                                                              
#define MAX 50                                                                  
#define RED 1                                                                
#define BLACK 0                                                                   
typedef struct tree{                                                                    
	int val;                                                                   
	char color:1;                                                               
	struct tree *left;                                                          
	struct tree *right;                                                         
	struct tree *parent;                                                        
}rbtree;                                                                              

rbtree *insert(rbtree *, int);                                           
rbtree *create(rbtree *, int);                                           
void print(rbtree *);                                                        
void inorder(rbtree *);                                                        
rbtree *alternode(rbtree *, rbtree *);                                     
rbtree *right_rotategp(rbtree *, rbtree *);                                 
rbtree *left_rotategp(rbtree *, rbtree *);                                  
void right_rotate(rbtree *);                                                   
void left_rotate(rbtree *);                                                    
