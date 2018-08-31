
/*
 * File:insert.c
 * Description:inserting a node a node for RB tree
 * Author:Shrishail Satihal
 * Date:23-8-18
 * Last modified:23-8-18
 * Last modified by:Shrishail Satihal<s.shrishail@globaledgesoft.com>
 */

rbtree *insert_node(rbtree *root,
	int val) /*function definition for insert operation which takes argument
		  root which is apointer to structure rbtree and value of type
		  integer which returns pointer to structure rbtree*/
{
    rbtree *ptr = NULL;
    rbtree *prev = NULL;
    rbtree *newnode = NULL;
    int left;
    int right;

    if (root == NULL) {
	root = create_node(root, val);
	root->color = BLACK;
	return root;
    }
    ptr = root;
    while ((ptr != NULL) && ((ptr->val > val) || (ptr->val < val))) {
	if (ptr->val > val) { /*if the root value is greater than next given
				 input then traverse left and insert node*/
	    prev = ptr;
	    left = 1;
	    right = 0;
	    ptr = ptr->left;
	} else { /*if the root value is less than next given input traverse
		 right and insert node*/
	    prev = ptr;
	    left = 0;
	    right = 1;
	    ptr = ptr->right;
	}
    }
    if (ptr == NULL) {
	if (left) {
	    newnode = create_node(prev, val);
	    prev->left = newnode;
	} else if (right) {
	    newnode = create_node(prev, val);
	    prev->right = newnode;
	}
	root = alternode(root, newnode);
	return root;
    }
} /*end of insert node function*/

