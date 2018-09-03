/**
 * File              : right_rotate_from_parent.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to right rotate from parent
 * \param parent address
 * \return Returns tree root address
 * */
bst_t *right_rotate_from_parent(bst_t **parent)
{
    (*parent)->left->right = *parent;  /* Swapping addresses */
    (*parent)->left->prev = (*parent)->prev;

    (*parent)->prev->right = (*parent)->left;
    (*parent)->left = NULL;
    (*parent)->prev = (*parent)->prev->right;

    return left_rotate_from_gp(&(*parent)->prev);/* Function call to
						      left rotate from
						      grand parent */
}
