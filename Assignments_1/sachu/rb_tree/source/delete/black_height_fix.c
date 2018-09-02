/**
 * File              : black_height_fix.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 19.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function to fix black height property
 * \brief Applied case - Node, parent and sibling are black
 * \param d_node stores address of node to be deleted
 * \param root stores address of root of tree
 * */
void black_height_fix(bst_t **d_node, bst_t **root)
{
    int color = MAX;
    bst_t *grand_p = (*d_node)->prev->prev;  /* /Grand parent node */

    /* Case - Parent right side child case */
    if ((*d_node)->prev == grand_p->right) {
	bst_t *uncle = grand_p->left;     /* Uncle node */

	if (uncle->color == RED) {  /* Sub case - Uncle red */
	    bst_t *new = uncle->right;

	    *root = right_rotate_from_gp(&uncle);/* Function call to
						    right rotate from
						    grand parent */
	    if ((*d_node)->prev->right == (*d_node)) {
		(*d_node)->prev->left->color = RED;
		(*d_node)->prev->right = NULL;
	    } else {
		(*d_node)->prev->right->color = RED;
		(*d_node)->prev->left = NULL;
	    }

	    grand_p->left = new;
	    new->prev = grand_p;
	    free(*d_node);
	} else {                /* Sub case - Uncle black */
	    bst_t *new = uncle->right;

	    color = grand_p->color;

	    *root = right_rotate_from_gp(&uncle); /* Function call to
						     right rotate from
						     grand parent */

	    uncle->color = color;
	    if ((*d_node)->prev->right == (*d_node)) {
		(*d_node)->prev->left->color = RED;
		(*d_node)->prev->right = NULL;
	    } else {
		(*d_node)->prev->right->color = RED;
		(*d_node)->prev->left = NULL;
	    }

	    if (new->color == RED) {
		grand_p->color = BLACK;
		uncle->left->color = BLACK;
	    }

	    grand_p->left = new;
	    new->prev = grand_p;
	    free(*d_node);
	}
    } else {                    /* Case - Parent left child case */
	bst_t *uncle = grand_p->right;
	bst_t *new = uncle->left;

	if (uncle->color == RED) {  /* Sub case - Uncle color Red */

	    *root = left_rotate_from_gp(&uncle); /* Function call to left
						    rotate from
						    grand parent*/

	    if ((*d_node)->prev->right == (*d_node)) {
		(*d_node)->prev->left->color = RED;
		(*d_node)->prev->right = NULL;
	    } else {
		(*d_node)->prev->right->color = RED;
		(*d_node)->prev->left = NULL;
	    }

	    grand_p->right = new;
	    new->prev = grand_p;
	    free(*d_node);
	} else {            /* Sub case - Uncle color Black */
	    color = grand_p->color;

	    *root = left_rotate_from_gp(&uncle);  /* Function call to
						     left rotate from
						     grand parent */

	    uncle->color = color;
	    if ((*d_node)->prev->right == (*d_node)) {
		(*d_node)->prev->left->color = RED;
		(*d_node)->prev->right = NULL;
	    } else {
		(*d_node)->prev->right->color = RED;
		(*d_node)->prev->left = NULL;
	    }

	    if (new->color == RED) {
		grand_p->color = BLACK;
		uncle->right->color = BLACK;
	    }

	    grand_p->right = new;
	    new->prev = grand_p;
	    free(*d_node);
	}
    }
}
