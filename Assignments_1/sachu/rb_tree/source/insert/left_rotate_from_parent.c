/**
 * File              : left_rotate_from_parent.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to left rotate from parent
 * \param parent node address
 * \return Returns root of tree
 * */
bst_t *left_rotate_from_parent(bst_t **parent)
{

    (*parent)->right->left = *parent;     /* Swapping addresses */
    (*parent)->right->prev = (*parent)->prev;

    (*parent)->prev->left = (*parent)->right;
    (*parent)->right = NULL;
    (*parent)->prev = (*parent)->prev->left;

    return right_rotate_from_gp(&(*parent)->prev);  /* Calling right
						       rotate function */
}
