
/**
 * File:print.c
 * Description:Printing the nodes of rbtree.
 * Date:12-7-18
 * Last modified:23-8-18
 * Last modified by:Shrishail Satihal<s.shrishail@globaledgesoft.com>
 */

void print(rbtree *root) /*function definition for printing a nodes
			   which takes arguments root is pointer to a
			   structure of type rbtree and returns void*/
{
    inorder(root); /*function call for inorder traversal*/
} /*end of print function*/

void inorder(rbtree *root) /*function definition for inorder traversal
			     which takes argument root which is a pointer
			     to structure and returns void*/
{
    if (root != NULL) {
	inorder(root->left);
	printf("%d\t", root->val);
	if (root->color) {
	    printf("RED\n");
	} else {
	    printf("BLACK\n");
	}
	inorder(root->right);
    }
} /*end of inorder function*/
