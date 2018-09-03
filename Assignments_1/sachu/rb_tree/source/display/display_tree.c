/**
 * File              : display_tree.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Display function to print elements of tree
 * \param root stores address of root of tree
 * */

void display_tree(bst_t *root)
{
    int value;
    char choice[SIZE];

    if (root == NULL) {
	printf("Tree is empty\n");
	return;
    }

    system("clear");
    printf("Choose order of printing\n"); /* Prompt for evaluation
					     order */
    printf("1.In_order\n2.Pre_order\n3.Post_order\n");

    fgets(choice, SIZE, stdin);
    __fpurge(stdin);
    value = atoi(choice);

    switch (value) {
	case 1:
	    printf("In order evaluation of tree\n");
	    in_order(root);   /* In order evaluation */
	    break;

	case 2:
	    printf("Pre order evaluation of tree\n");
	    pre_order(root);  /* Pre order evaluation */
	    break;

	case 3:
	    printf("Post order evaluation of tree\n");
	    post_order(root);  /* Post order evaluation */
	    break;

	default:
	    printf("ERROR!Invalid input\n");
	    break;
    }
}
/**
 * \brief Function definition for in order
 * \param root is a pointer storing tree root
 * */
void in_order(bst_t *root)
{
    if (root != NULL) {
	in_order(root->left);     /* Recursively moving to left node */
	printf("data = %d  color = %s\n", root->data, COLOR);
	in_order(root->right);   /* Recursively moving to right node */
    }
}

/**
 * \brief Function definition for pre order
 * \param root is a pointer storing tree root
 * */
void pre_order(bst_t *root)
{
    if (root != NULL) {
	printf("data = %d  color = %s\n", root->data, COLOR);

	pre_order(root->left);  /* Recursively moving to left
				   and right nodes */
	pre_order(root->right);
    }
}

/**
 * \brief Function definition for post order
 * \param root is a pointer storing tree root
 * */
void post_order(bst_t *root)
{
    if (root != NULL) {
	post_order(root->left);  /* Recursively moving to left
				    and right nodes */
	post_order(root->right);

	printf("data = %d  color = %s\n", root->data, COLOR);
    }
}
