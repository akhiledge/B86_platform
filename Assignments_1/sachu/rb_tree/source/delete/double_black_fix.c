/**
 * File              : double_black_fix.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 21.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to fix double black issue
 * \param d_node is a pointer storing address of node to be deleted
 * \param root stores address of root of tree
 * */
void double_black_fix(bst_t **d_node, bst_t **root)
{

    if ((*d_node)->prev->right == (*d_node)) { /* Node is a right
						  child */
	bst_t *ttemp = (*d_node)->prev->left;

	if ((*d_node)->prev->left->color == RED) {  /* Sibling red with
						       black children*/
	    bst_t *temp = (*d_node)->prev->left->right;

	    temp->color = RED;

	    *root = right_rotate_from_gp(&ttemp);  /* Right rotating */

	    (*d_node)->prev->color = BLACK;
	    (*d_node)->prev->left = temp;
	    temp->prev = (*d_node)->prev;

	    temp->prev->right = NULL;
	    free(*d_node);
	} else {                                /* Sibling black case */
	    bst_t *temp = (*d_node)->prev->left;

	    if ((*d_node)->prev->color == BLACK) { /* Parent of node
						      Black case */

		/* Sub case - Black Sibling with no children */
		if (temp->left == NULL && temp->right == NULL) {
		    if ((*d_node)->prev->prev == NULL) { /* Parent root
							    case */
			temp->color = RED;
			temp->prev->right = NULL;
			free(*d_node);
		    } else {     /* Function call to fix black height */
			black_height_fix(d_node, root);
		    }
		} else if (temp->left == NULL) {  /* Sub case - Right
						     red child only for
						     black sibling */
		    *root = left_rotate_from_parent(&temp);

		    temp->right = NULL;
		    (*d_node)->prev->color = BLACK;
		    (*d_node)->prev->right = NULL;
		    free(*d_node);
		} else if (temp->right == NULL) {  /* Sub case - Left red
						      child only for
						      black sibling */
		    *root = right_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->left->color = BLACK;
		    temp->right->color = BLACK;
		    (*d_node)->prev->right = NULL;
		    free(*d_node);
		} else {               /* Sub case - Black Sibling with
					  two children */
		    bst_t *new = temp->right;

		    temp->left->color = BLACK;

		    *root = right_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->right->right = NULL;
		    temp->right->left = new;
		    new->prev = temp->right;
		    temp->right->color = BLACK;
		    free(*d_node);
		}
	    } else {                     /* Parent of node Red case */

		/* Sub case - Sibling with no children */
		if (temp->left == NULL && temp->right == NULL) {
		    temp->color = RED;
		    (*d_node)->prev->color = BLACK;
		    (*d_node)->prev->right = NULL;
		    free(*d_node);
		} else if (temp->right == NULL) {   /* Sub case - Left
						       red child only for
						       sibling */
		    *root = right_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->right->color = RED;
		    (*d_node)->prev->right = NULL;
		    free(*d_node);
		} else if (temp->left == NULL) { /* Sub case - Right red
						    child only for
						    sibling */
		    *root = left_rotate_from_parent(&temp);
		    temp->color = RED;
		    (*d_node)->prev->color = RED;
		    (*d_node)->prev->right = NULL;
		    free(*d_node);
		} else {                   /* Sub case - Sibling with
					      two children */
		    bst_t *new = temp->right;

		    temp->left->color = BLACK;

		    *root = right_rotate_from_gp(&temp);

		    temp->right->right = NULL;
		    temp->right->left = new;
		    new->prev = temp->right;
		    free(*d_node);
		}
	    }
	}
    } else {                 /* Node is a left child */
	bst_t *ttemp = (*d_node)->prev->right;

	if ((*d_node)->prev->right->color == RED) {  /* Sibling red with
							black children */
	    bst_t *temp = (*d_node)->prev->right->left;

	    temp->color = RED;

	    *root = left_rotate_from_gp(&ttemp);

	    (*d_node)->prev->color = BLACK;
	    (*d_node)->prev->right = temp;
	    temp->prev = (*d_node)->prev;
	    temp->prev->left = NULL;
	    free(*d_node);
	} else {                     /*Sibling black case */
	    bst_t *temp = (*d_node)->prev->right;

	    if ((*d_node)->prev->color == BLACK) {   /* Sub case - Parent
							node Black */

		/* Sub case - Black Sibling with no children */
		if (temp->left == NULL && temp->right == NULL) {
		    if ((*d_node)->prev->prev == NULL) {
			temp->color = RED;
			temp->prev->left = NULL;
			free(*d_node);
		    } else {
			black_height_fix(d_node, root);
		    }
		} else if (temp->right == NULL) {    /* Sub case - Left
							red child only
							for black
							sibling */
		    *root = right_rotate_from_parent(&temp);

		    temp->left = NULL;
		    (*d_node)->prev->color = BLACK;
		    (*d_node)->prev->left = NULL;
		    free(*d_node);
		} else if (temp->left == NULL) {   /* Sub case - Right
						      red child only for
						      black sibling */
		    *root = left_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->left->color = BLACK;
		    temp->right->color = BLACK;
		    (*d_node)->prev->left = NULL;
		    free(*d_node);
		} else {             /* Sub case - Black Sibling
					with two children */
		    bst_t *new = temp->left;
		    *root = left_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->left->color = BLACK;
		    temp->right->color = BLACK;
		    temp->left->left = NULL;
		    temp->left->right = new;
		    new->prev = temp->left;
		    free(*d_node);
		}
	    } else {               /* Case - Parent node red */

		/* Sub case - Black Sibling with no children */
		if (temp->left == NULL && temp->right == NULL) {
		    temp->color = RED;
		    (*d_node)->prev->color = BLACK;
		    (*d_node)->prev->left = NULL;
		    free(*d_node);
		} else if (temp->left == NULL) {     /* Sub case - Black
							Sibling with
							right child */
		    *root = left_rotate_from_gp(&temp);

		    temp->color = BLACK;
		    temp->left->color = RED;
		    (*d_node)->prev->left = NULL;
		    free(*d_node);
		} else if (temp->right == NULL) {   /* Sub case - Black
						       Sibling with left
						       child */
		    *root = right_rotate_from_parent(&temp);

		    temp->color = RED;
		    (*d_node)->prev->color = RED;
		    (*d_node)->prev->left = NULL;
		    free(*d_node);
		} else {                  /* Sub case - Black Sibling
					     with two children */
		    bst_t *new = temp->left;

		    temp->right->color = BLACK;

		    *root = left_rotate_from_gp(&temp);

		    temp->left->left = NULL;
		    temp->left->right = new;
		    new->prev = temp->right;
		    free(*d_node);
		}
	    }
	}
    }
}
