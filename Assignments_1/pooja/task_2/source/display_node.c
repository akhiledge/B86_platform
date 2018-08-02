/**@brief Function definition to display particular node
*@param pointer disp_node of type NODE
 */
void display_node(NODE *disp_node)
{
	int i = 0;				/*!< index*/

	printf("DATA in NODE\n");
	printf("%s\n", disp_node->data);
	for(i = 0; disp_node->count[i]; i++){					///number of files
		printf("Counts in %s file - %d\n", disp_node->filename[i], disp_node->count[i]);
	}
}
