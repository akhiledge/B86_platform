/**
 * File              : rbt_main.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 13.07.2018
 * Last Modified Date: 01.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Red Black tree operations
 * \Operations are insert delete and display
 * */

int main(void)
{
    int option;       /**< option is integer to accept user input */
    int value;        /**< value to store integer element */
    char loop;        /**< loop to control looping */
    char input[SIZE];
    bst_t *root = NULL;  /**< Root of tree of type bst_t */

    do {
	printf("**********************\n");
	printf("Enter your choice\n");  /* Prompt for user input */
	printf("1.Insert_Element\n2.Delete_Element\n");
	printf("3.Search_Element\n4.Display_Tree\n5.Exit\n");

	fgets(input, SIZE, stdin);
	option = atoi(input);
	__fpurge(stdin);

	switch (option) {
	    case 1:
		do {
		    printf("Enter the element to be added\n");
		    fgets(input, SIZE, stdin);
		    value = my_atoi(input);

		} while (value == INVALID);
		insert_element(&root, value); /* Function call
						 for inserting element */
		break;
	    case 2:
		delete_element(&root);    /* Function call to
					     delete a node */
		break;
	    case 3:
		search_tree(root);
		break;
	    case 4:
		display_tree(root);          /* Function call to
						display tree */
		break;
	    case 5:
		return 0;
	    default:
		printf("Invalid input\n");
		break;
	}

	printf("Do you want to continue[y/n]\n");
	loop = getchar();
	__fpurge(stdin);

    } while ((loop == 'y') || (loop == 'Y'));
    return 0;
}
