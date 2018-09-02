/**
 * File              : find_min.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 21.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief To find the minimum value in the tree
 * \root stores the root address of tree
 * */

void find_min(bst_t *root)
{
    if (root == NULL) {        /* Checking for empty tree */
	printf("Tree already empty\n");
	return;
    }
    bst_t *temp = find_min_element(root);   /* Function call to find
					       minimum */
    printf("Minimum value in tree is %d\n", temp->data);
}

bst_t *find_min_element(bst_t *root)
{
    if (root->left != NULL) {           /* Recursively moving to
					     left node */
	return find_min_element(root->left);
    }
    return root;
}
