///@brief Program to insert and display node in RB tree
int main()
{
	///Variable declaration
	int choice = 0;
	int data = 0;					
	char *str = NULL;
	RB_TREE *root = NULL;			/*!<root of the tree>*/

	str = (char *) malloc(MAX);
	assert(str);

	while(1){
		printf("Enter choice\n");
		printf("1. Insert node\n2. Display\n3. Exit\n");
		fgets(str, MAX, stdin);
		assert(str);
		choice = atoi(str);									///choice of function

		switch(choice){
			case 1: printf("Enter a number\n");					/*To get data and call insert function*/
					fgets(str, MAX, stdin);
					data = atoi(str);
					root = insert_node(root, data);	
					break;

			case 2: display(root);								///display function call
					break;

			case 3: exit(0);

			default: printf("Invalid option\n");
		}
	}
}
