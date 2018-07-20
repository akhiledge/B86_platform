#ifndef RB_HEADER_H
#define RB_HEADER_H
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define MAX 30
#define BLACK 0
#define RED 1
struct tree{
	int data;
	char color:1;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
};
typedef struct tree RB_TREE;

RB_TREE *insert_node(RB_TREE *, int);
RB_TREE *create_node(RB_TREE *, int);
void display(RB_TREE *);
void inorder(RB_TREE *);
void preorder(RB_TREE *);
void postorder(RB_TREE *);

RB_TREE *modify_node(RB_TREE *, RB_TREE *);
RB_TREE *right_rotate_gp(RB_TREE *, RB_TREE *);
void left_rotate(RB_TREE *);
RB_TREE *left_rotate_gp(RB_TREE *, RB_TREE *);
void right_rotate(RB_TREE *);
#endif


