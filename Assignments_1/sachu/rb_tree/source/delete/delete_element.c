/**
 * File              : delete_element.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Function to delete a particular node from tree
 * \param root pointer stores address of root of tree
 * */

void delete_element(bst_t **root)
{
    int value;
    char str[SIZE];

    if (*root == NULL) {      /* Checking for empty tree */
	printf("Tree already empty\n");
	return;
    }

    do {                    /* Prompt for element to be deleted */
	printf("Enter the element to be deleted\n");
	fgets(str, SIZE, stdin);
	__fpurge(stdin);

	value = my_atoi(str);
    } while (value == INVALID);

    delete_node_value(root, value);  /* Function call to delete node */
}

/**
 * \brief Function definition to find node to be deleted
 * \param root pointer stores address of root of tree
 * */
void delete_node_value(bst_t **root, int value)
{
    bst_t *ptr = *root;

    if (*root == NULL) {
	printf("Tree is empty\n");
	return;
    }
    while (1) {
	if (ptr->data > value) {
	    ptr = ptr->left;       /* Left traversal */
	} else if (ptr->data < value) {
	    ptr = ptr->right;      /* Right traversal */
	}
	if (ptr == NULL) {
	    printf("Element not found\n");
	    return;
	}
	if (ptr->data == value) {
	    operation_delete(root, ptr); /* Function call for
					    delete operation */
	    return;
	}
    }
}

/**
 * \brief Function definition to delete node of different conditions
 * \param root pointer stores address of root of tree
 * \param d_node pointer stores address of node to be deleted
 * */
void operation_delete(bst_t **root, bst_t *d_node)
{

    /* Node with no children */
    if (d_node->left == NULL && d_node->right == NULL) {
	if (d_node->prev != NULL) {
	    if (d_node->color == RED) {  /* Node color red case */
		if (d_node->prev->left == d_node) { /* Left case */
		    d_node->prev->left = NULL;

		} else {
		    d_node->prev->right = NULL;   /* Right case */
		}
		free(d_node);

	    } else {      /* Function call to fix double black issue
			     - Black node case */
		double_black_fix(&d_node, root);
	    }
	} else {  /* Single node case */
	    free(d_node);
	    *root = NULL;
	}

    } else if (d_node->left == NULL) {  /* Node with right child */
	d_node->data = d_node->right->data;
	free(d_node->right);
	d_node->right = NULL;

    } else if (d_node->right == NULL) { /* Node with left child */
	d_node->data = d_node->left->data;
	free(d_node->left);
	d_node->left = NULL;

    } else {                    /* Node with two child case */
	/* Function call to find inorder successor and copying data */
	bst_t *temp = find_min_element(d_node->right);

	d_node->data = temp->data;
	operation_delete(root, temp);   /* Call for delete */

    }
}
