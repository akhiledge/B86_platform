/**
 * File              : create_node_function.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 23.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: Function to create node
 *@param: str is the word read from file
 *@return: returns new node created
 */

NODE *create_node(char *str)
{
	NODE *new = NULL;						/**struct node ptr to new node*/
	new = (NODE *) malloc(sizeof(NODE));
	assert(new);							/**malloc validation for new*/
	new->data = (char *) malloc(SIZE);
	assert(new->data);						/**malloc validation for
											new->data*/
	strcpy(new->data, str);					/**populating structure members*/
	memset(new->count, 0, MAX);
	new->next = NULL;
	
	return new;
}
