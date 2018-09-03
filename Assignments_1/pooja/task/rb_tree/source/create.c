/**
 * File              : create.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 13.07.2018
 * Brief			 : File containing function to create nodes
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/*@brief: insert_node function to insert nodes to RB tree
 *@param: root node of the tree of type RB_TREE, data to be inserted									into node of type int
 *@return: returns the root node pointer to main function
 */

RB_TREE *create_node(RB_TREE *prev, int data)
{
	RB_TREE *new = NULL; /**@var: variable for new node*/

	new = (RB_TREE *)malloc(sizeof(RB_TREE));
	assert(new); /**malloc validation*/
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->color = RED;
	new->parent = prev;
	return new;
}
