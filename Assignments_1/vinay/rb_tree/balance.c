/**
 * File              : balance.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */

/**
 *\brief balance the tree after an insertion
 */
extern node *root;
void
balance(node *great_grandparent, node *grandparent, node *parent,
		enum side child_pos)
{
	node   *siblings = NULL;
	bool    color;

	if (BLACK == (parent->color))
		return;
	else {
		if (grandparent != NULL)
			siblings = sibling(parent, grandparent);
		if (siblings == NULL)
			color = BLACK;
		else
			color = siblings->color;
		if (color == RED) {
			(grandparent->color) = !(grandparent->color);
			(parent->color) = !(parent->color);
			(siblings->color) = !(siblings->color);
		} else {
			switch (child_pos) {
				case leftright:
					(grandparent->left) = left_rotate(parent);
				case leftleft:{
						if (great_grandparent != NULL) {
							grandparent = (great_grandparent->left);
							parent = (grandparent->left);
							(great_grandparent->left) =
									right_rotate(grandparent);
						} else {
							grandparent = parent;
							parent = (grandparent->left);
							root = right_rotate(grandparent);
						}
						(parent->color) = !(parent->color);
						(grandparent->color) = !(grandparent->color);
						break;
					}
				case rightleft:
					(grandparent->right) = right_rotate(parent);

				case rightright:{
						if (great_grandparent != NULL) {
							grandparent = (great_grandparent->right);
							parent = (grandparent->right);
							(great_grandparent->right) =
									left_rotate(grandparent);
						} else {
							grandparent = parent;
							parent = (grandparent->right);
							root = left_rotate(grandparent);
						}
						(parent->color) = !(parent->color);
						(parent->left->color) = !(parent->left->color);
						break;
					}
			}
		}
	}
	return;
}
