///Function to insert node
RB_TREE *insert_node(RB_TREE *root, int data)
{
	RB_TREE *prev = NULL;
	if(root == NULL)
	return (create_node(prev, data));
	if(data > root->data)
	root->right = insert_node(root->right, data);
	else if(data < root->data)
	root->left = insert_node(root->left, data);
	else
	printf("No duplicates allowed\n");
	prev = root;
	return root;
}
