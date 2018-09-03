/**
 * File              : bst_insert.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 02.09.2018
 * Brief			 : Function to insert node and invokes modify function
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/*@brief: insert_node function to insert nodes to RB tree
 *@param: root node of the tree of type RB_TREE, data to be inserted
 in node of type int
 *@return: returns the root node pointer to main function
 */

RB_TREE *insert_node(RB_TREE *root, int data)
{
	RB_TREE *temp = NULL; /*!@var: node to traverse tree*/
	RB_TREE *prev = NULL; /*!@var: node to keep track of previous node*/
	RB_TREE *new = NULL; /*!@var: new node inserted*/
	int left = 0;
	int right = 0;

	if (root == NULL) { /**if tree is empty, insert node
						  which becomes root*/
		root = create_node(root, data); /**create_node function call*/
		root->color = BLACK; /**root node has to be black*/
		return root;
	}

	temp = root;
	while ((temp != NULL) && ((temp->data > data) || (temp->data < data))) {
		/**traversing the tree*/
		if (temp->data > data) {
			prev = temp;
			left = 1;
			right = 0;
			temp = temp->left;
		} else {
			prev = temp;
			left = 0;
			right = 1;
			temp = temp->right;
		}
	}

	if (temp == NULL) {
		if (left) {
			new = create_node(prev, data);
			prev->left = new;
		}
		else if (right) {
			new = create_node(prev, data);
			prev->right = new;
		}
		printf("Node inserted\n");
		root = modify_node(root, new);
		return root;
	} else { /**if duplicate is alreday present*/
		printf("Sorry!! No duplicates allowed\n");
		return root;
	}
}
