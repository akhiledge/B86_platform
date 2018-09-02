/**
 * File              : right_rotate_from_gp.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to right rotate from grand parent
 * \param parent node address
 * \return Returns root of tree
 * */
bst_t *right_rotate_from_gp(bst_t **parent)
{
    bst_t *temp;

    (*parent)->right = (*parent)->prev;  /* Swapping addressses */
    temp = (*parent)->prev->prev;

    if (temp != NULL) {
	if (temp->left  == (*parent)->prev) {
	    (*parent)->prev->prev->left = *parent;
	} else {
	    (*parent)->prev->prev->right = *parent;
	}
    }

    (*parent)->prev->prev = *parent;
    (*parent)->prev->left = NULL;
    (*parent)->prev = temp;

    (*parent)->color = ((*parent)->color) ^ MAX; /* Changing colors of
						    parent and grand
						    parent */
    (*parent)->right->color = ((*parent)->right->color) ^ MAX;

    return find_root(*parent); /* Finding root */
}
