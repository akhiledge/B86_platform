/**
 * File              : create_node.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition for creating node
 * \param parent address
 * \param value stores the new element
 * \return Created node address
 * */
bst_t *create_node(bst_t *parent, int value)
{
    bst_t *new = (bst_t *) malloc(sizeof(bst_t)); /* Dynamic allocation
    of memory */
    assert(new);

    new->prev = parent; /* Assigning addresses and inserting value */
    new->data = value;
    new->color = RED;
    new->left = NULL;
    new->right = NULL;
    if (parent == NULL) {     /* Root node */
	new->color = BLACK;
    }
    return new;
}
