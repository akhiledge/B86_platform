
/*
 * File:create.c
 * Description:creating a node for RB tree
 * Author:Shrishail Satihal
 * Date:12-7-18
 * Last modified:23-8-18
 * Last modified by:Shrishail Satihal<s.shrishail@globaledgesoft.com>
 */

rbtree *create_node(rbtree *root,
	int val) /*Function definition for creating a nod which takes an
		   arguments root which is pointer to a structure of rbtree
		   and value is of type integer and it returns pointer
		   to structure rbtree*/
{
    rbtree *newnode = NULL;

    newnode = (rbtree *)malloc(sizeof(rbtree));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->color = RED;
    newnode->parent = root;
    return newnode;
} /*end of create node function*/
