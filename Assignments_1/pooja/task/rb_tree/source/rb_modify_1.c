/**
 * File              : rb_modify_1.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 14.07.2018
 * Brief			 : File containing function to modify the node
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/*@brief: Function  definition to modify node
 *@param: root node of type RB_TREE, data of type int
 *@return: Returns root
 */

RB_TREE *modify_node(RB_TREE *root, RB_TREE *new)
{
	RB_TREE *parent = NULL; /*!<@var: parent node*/
	RB_TREE *grandparent = NULL; /*!<@var: grandparent node*/
	RB_TREE *uncle = NULL; /*!<@var: uncle node*/

	int index = 0;
	int LEFT1 = 0;
	int RIGHT1 = 0;
	int LEFT2 = 0;
	int RIGHT2 = 0;

	if (new->parent != root) { /**modify after height > 1*/
		parent = new->parent;
		grandparent = new->parent->parent;
		if (parent->color) { /**if parent is red, check uncle*/
			if (grandparent->left != parent) {/**get uncle node's address*/
				uncle = grandparent->left;
			} else {
				uncle = grandparent->right;
			}

			if (uncle == NULL || (uncle->color == BLACK)) {	/**if parent
															  is red & uncle is black*/
				if (grandparent->left == parent) { /**To get the details
													 about 4 cases*/
					LEFT1 = 1;
				} else {
					RIGHT1 = 1;
				}
				if (parent->left == new) {
					LEFT2 = 1;
				} else {
					RIGHT2 = 1;
				}
				if (LEFT1 & LEFT2) { /**Left Left case*/
					root = right_rotate_gp(root, grandparent);
				}
				else if (LEFT1 & RIGHT2) { /**Left Right case*/
					left_rotate(parent);
					root = right_rotate_gp(root, grandparent);
				}
				else if (RIGHT1 & RIGHT2) {	/**Right Right case*/
					root = left_rotate_gp(root, grandparent);
				}
				else if (RIGHT1 & LEFT2) { /**Right left case*/
					right_rotate(parent);
					root = left_rotate_gp(root, grandparent);
				}
				return root;	
			} else { /**if parent is red, uncle is red(change colors
					   of parent,uncle and grandparent nodes*/
				parent->color = BLACK;
				uncle->color = BLACK;
				if (grandparent != root) {
					grandparent->color = RED;
				}
				return root;
			}
		}
	}
	return root;
}

/*@brief: Function definition to right rotate grandparent node
 *@param: root node and grandparent node of type RB_TREE
 *@return: Returns root node of type RB_TREE
 */
RB_TREE *right_rotate_gp(RB_TREE *root, RB_TREE *grandparent)
{
	RB_TREE *parent = grandparent->left;
	grandparent->left = parent->right;
	parent->right = grandparent;
	if ((grandparent->parent != NULL) && (grandparent->parent->left == grandparent)) {
		grandparent->parent->left = parent;
	} else {
		grandparent->parent->right = parent;
	}
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->color = RED;
	parent->color = BLACK;

	if (parent->parent == NULL) {
		root = parent;
		return root;
	}
	return root;
}

/*@brief: Function definition to left rotate parent node
 *@param: parent node of type RB_TREE
 *@return: Returns void
 */
void left_rotate(RB_TREE *parent)
{
	RB_TREE *child = parent->right;
	parent->parent->left = child;
	child->parent = parent->parent;
	parent->parent = child;
	if (parent->left != NULL) {
		parent->left->parent = child;
	}
	child->right = parent->left;
	child->left = parent;

	parent->left = NULL;
	parent->right = NULL;
}

/*@brief: Function definition to left rotate grandparent node
 *@param: root node and grandparent node of type RB_TREE
 *@return: Returns root node of type RB_TREE
 */
RB_TREE *left_rotate_gp(RB_TREE *root, RB_TREE *grandparent)
{
	RB_TREE *parent = grandparent->right;
	grandparent->right = parent->left;
	parent->left = grandparent;
	if ((grandparent->parent != NULL)
			&& (grandparent->parent->left == grandparent)) {
		grandparent->parent->left = parent;
	} else {
		grandparent->parent->right = parent;
	}
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->color = RED;
	parent->color = BLACK;

	if (parent->parent == NULL) {
		root = parent;
		return root;
	}
	parent->parent->right = parent;
	return root;
}
/*@brief: Function definition to right rotate parent node
 *@param: parent node of type RB_TREE
 *@return: Returns void
 */

void right_rotate(RB_TREE *parent)
{
	RB_TREE *child = parent->left;
	parent->parent->right = child;
	child->parent = parent->parent;
	parent->parent = child;
	if (parent->right != NULL) {
		parent->right->parent = child;
	}
	child->left = parent->right;
	child->right = parent;

	parent->left = NULL;
	parent->right = NULL;
}
