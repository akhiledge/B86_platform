/**
 * File              : main.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 13.07.2018
 * Brief			 : RB tree insertion of nodes
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: main function to take input from user and invoke function
  @param: No arguments
 *@return: Returns 0 on success
 */
int main(void)
{
	int choice = 0;
	int data = 0;
	char *str = NULL;
	RB_TREE *root = NULL; /*!<@var: root of the tree>*/

	str = (char *) malloc(MAX);
	assert(str); /**Malloc validation*/

	while (1) {
		printf("Enter choice\n");
		printf("1. Insert node\n2. Display\n3. Exit\n");
		fgets(str, MAX, stdin);
		assert(str); /**malloc validation*/
		choice = atoi(str); /**choice of function*/

		switch (choice) {
		case 1: printf("Enter a number\n"); /**To get data from user*/
				fgets(str, MAX, stdin);
				data = atoi(str);
				root = insert_node(root, data); /**insert_node function
												call*/
				break;

		case 2: display(root); /**display function call*/
					break;

		case 3: printf("Exiting\n");
				exit(0); /**Exit from the program*/

		default: printf("Invalid option\n");
		}
	}
}
