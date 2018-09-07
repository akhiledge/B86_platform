/**
 * File              : search_content.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: Function definition to search the particular content and return
*@param: str contains the input string from user
*@return: 0 on success, -1 on failure*/
int search(char *str)
{
	NODE *traverse = NULL;							/**struct node ptr to
													  traverse list*/
	int index = 0;									/**variable for hashtable
													  index*/
	char *msg = NULL;
	
	index = hash_func(*str);						/**calling hash function*/
	if (hashtable[index] == NULL) {						/**if no entry present*/
		return -1;
	} else {
		traverse = hashtable[index];					/**if entry present,
														traverse through list*/
		while (traverse != NULL) {
			if (strcasecmp(traverse->data, str) == 0) {	/**if string matches
														print details about
														node*/
				display_node(traverse);
				return 0;								/**returns 0 on
														 success*/
			}
			traverse = traverse->next;
		}
			return -1;									/**returns -1 if not
														found*/
	}
}
