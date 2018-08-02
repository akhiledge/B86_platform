/**Function to create node*/

NODE *create_node(char *str)
{
	NODE *new = NULL;				///struct node ptr to new node
	new = (NODE *) malloc(sizeof(NODE));
	assert(new);							///malloc validation for new
	new->data = (char *) malloc(SIZE);
	assert(new->data);						///malloc validation for new
	//new->filename[MAX] = {NULL};
	strcpy(new->data, str);					///populating structure members
	memset(new->count, 0, MAX);
	new->next = NULL;
	
	return new;						/**@return struct node new*/
}
