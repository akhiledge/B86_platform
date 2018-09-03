/**
 * File              : display.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 13.07.2018
 * Brief			 : File containing function to display nodes
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/*@brief: Display function to invoke inorder, Preorder
 *			and postorder functions
 * @param: root node of type RB_TREE
 * @return: returns void
 * */

void display(RB_TREE *root)
{
	printf("INORDER:\n");
	inorder(root);
	printf("PREORDER:\n");
	preorder(root);
	printf("POSTORDER:\n");
	postorder(root);
}

/*@brief: Recursive function to display nodes inorder
 * @param: root node of type RB_TREE
 * @return: returns void
 * */
void inorder(RB_TREE *root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("%d\t", root->data);
		root->color ? printf("RED\n") : printf("BLACK\n");
		inorder(root->right);
	}
}
/*@brief: Recursive function to display nodes in preorder
 * @param: root node of type RB_TREE
 * @return: returns void
 * */
void preorder(RB_TREE *root)
{
	if (root != NULL) {
		printf("%d\t", root->data);
		root->color ? printf("RED\n") : printf("BLACK\n");
		preorder(root->left);
		preorder(root->right);
	}
}
/*@brief: Recursive function to display nodes in postorder
 * @param: root node of type RB_TREE
 * @return: returns void
 * */
void postorder(RB_TREE *root)
{
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d\t", root->data);
		root->color ? printf("RED\n") : printf("BLACK\n");
	}
}
