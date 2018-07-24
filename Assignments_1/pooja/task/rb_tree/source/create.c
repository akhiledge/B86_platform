///Function to create node
RB_TREE *create_node(RB_TREE *prev, int data)
{
	RB_TREE *new = NULL;				///variable for new node
	new = (RB_TREE *)malloc(sizeof(RB_TREE));
	assert(new);					///malloc validation
	new-> data = data;				
	new->left = NULL;
	new->right = NULL;
	new->color = RED;
	new->parent = prev;
	return new;
}
