/**
 * File              : search_tree.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Searching for any element present in tree or not
 * \param root stores root of tree
 * */
void search_tree(bst_t *root)
{
    int value;
    char str[SIZE];

    if (root == NULL) {   /* Empty tree case */
	printf("Tree already empty\n");
	return;
    }

    do {
	printf("Enter value to be searched\n"); /* Prompt for
						   search key */
	fgets(str, SIZE, stdin);
	__fpurge(stdin);

	value = my_atoi(str);
    } while (value == INVALID);

    root = search_element(root, value); /* Function call for searching */

    (root == NULL) ? printf("Value not found\n") :
	printf("%d Found : Color = %s\n", root->data, COLOR);
}

/**
 * \brief Function definition for search
 * \param root stores root of tree
 * \param value stores search element
 * */
bst_t *search_element(bst_t *root, int value)
{
    if (root != NULL) {
	if (root->data > value) {   /* Recursive search call till value
					 matches or NULL occurs */
	    return search_element(root->left, value);
	} else if (root->data < value) {
	    return search_element(root->right, value);
	} else {
	    return root;
	}
    }
    return NULL;
}
