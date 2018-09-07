/**
 * File              : display_node.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: Function definition to display particular node
*@param: pointer disp_node of type NODE
*@return: void
 */
void display_node(NODE *disp_node)
{
	int i = 0;				/*!< index*/

	printf("DATA in NODE\n");
	printf("%s\n", disp_node->data);
	for (i = 0; disp_node->count[i]; i++) {		/**to print count and
												  filename*/
		printf("Counts in %s file - %d\n", disp_node->filename[i], disp_node->count[i]);
	}
}
