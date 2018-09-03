/**
 * File              : left_rotate_from_gp.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to left rotate from grand parent
 * \param parent node address
 * \return Returns root of tree
 * */
bst_t *left_rotate_from_gp(bst_t **parent)
{
    bst_t *temp;

    (*parent)->left = (*parent)->prev;   /* Swapping addresses */
    temp = (*parent)->prev->prev;

    if (temp != NULL) {
	if (temp->left  == (*parent)->prev) {
	    (*parent)->prev->prev->left = *parent;
	} else {
	    (*parent)->prev->prev->right = *parent;
	}
    }

    (*parent)->prev->prev = *parent;
    (*parent)->prev->right = NULL;
    (*parent)->prev = temp;

    (*parent)->color = ((*parent)->color) ^ MAX;/* Changing colors of
						   parent and
						   grand parent */
    (*parent)->left->color = ((*parent)->left->color) ^ MAX;

    return find_root(*parent);   /* Finding root */
}
