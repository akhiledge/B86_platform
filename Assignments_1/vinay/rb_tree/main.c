/**
 * File              : main.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */

/**
 *\brief main function for rb tree
 **/
node   *root;
int
main(void)
{

	int     option = 0;
	int     data = 0;

	bool(*function[])() = {
	insert, inorder, preorder, postorder};

	while (true) {
		option = user_input();
		if ((option < 5) && (option > 1)) {
			(function[option - 1]) (root);
		} else {
			if (option == 1) {
				fputs("enter value: ", stdout);
				data = value_in_node();
				if (function[option - 1] (data)) {
					printf(" element %sted\n",
							(option == 1) ? "inser" : "dele");
				} else
					printf("%s found\n ",
							(option == 1) ? "duplicate" : "element not");
			} else if (option == 5) {
				return 0;
			} else {
				fputs("enter a valid option\n", stdout);
			}
		}
	}

	return 0;
}
