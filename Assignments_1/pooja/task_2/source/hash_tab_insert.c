/**
 * File              : hash_tab_insert.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 0.0.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: File contain function to insert file contents in
*					Hash table
*@param: str is the word to be inserted in hash table
*		file is the name of the file
*		argc is number of files
*@return: void*/

void insert(char *str, char *file, int argc)
{
	struct node *head = NULL;		/*!<struct node pointer used for
									  traversing linked list*/
	struct node *new = NULL;		/*!struct node ptr for new node*/
	struct node *prev = NULL;
	int index = 0;					/*!index of hashtable*/
	int i = 0;

	index = hash_func(*str);		/**call hash function*/
	if (hashtable[index] == NULL) {	/**initial condition*/
		new = create_node(str);		/**creation of new node*/
		hashtable[index] = new;		/**enter the new node address to
									  hash table, which is head node*/
		(new->count[0])++;			/**increment count to 1*/
		strcpy(new->filename[0], file);
		return;
	} else {
		head = hashtable[index];	/**ptr entry in hashtable is
									  head of linked list*/
		prev = NULL;				/**previous node*/
		while (head != NULL) {
			if (strcasecmp(str, head->data) == 0) { /**if the head node data
													  equal to the new data*/
				for (i = 0; i < (argc - 2); i++) { 
					if (strcmp(head->filename[i],file) == 0) {
						(head->count[i])++;			/**increment count*/
					}
					else {
						strcpy(head->filename[i+1], file);
						(head->count[i+1])++;
					}
					return;
				}
			}

			if (strcasecmp(str,head->data) < 0) {	/**if new data is smaller
													than the existing node*/
				new = create_node(str);				/**sort the nodes
													  based on data*/
				strcpy(new->filename[0], file);
				if (head == hashtable[index]) {

					hashtable[index] = new;
					new->next = head;
					(new->count[0])++;
				} else {
					new->next = prev->next;
					prev->next = new;
					(new->count[0])++;
				}
				return;
			}
			prev = head;					/**if not the previous
											conditions, traverse the list*/
			head = head->next;
		}

		if (head == NULL) {					/**if the new node has to be
											inserted at the end of list*/
			new = create_node(str);
			strcpy(new->filename[0],file);
			new->next = prev->next;
			prev->next = new;
			(new->count[0])++;
		}
	}	
}
