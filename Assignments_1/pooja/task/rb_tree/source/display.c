///@brief function to display the nodes
void display(RB_TREE *root)
{
	printf("INORDER:\n");
	inorder(root);
	printf("PREORDER:\n");
	preorder(root);
	printf("POSTORDER:\n");
	postorder(root);
}

///Inorder function(Recursive)
void inorder(RB_TREE *root)
{
	if(root != NULL){
		inorder(root->left);
		printf("%d\t", root -> data);
		root->color?printf("RED\n"):printf("BLACK\n");
		inorder(root -> right);
	}
}

///Preorder function(Recursive)
void preorder(RB_TREE *root)
{
	if(root != NULL){
		printf("%d\t", root -> data);
		root->color?printf("RED\n"):printf("BLACK\n");
		preorder(root->left);
		preorder(root -> right);
	}
}
///Postorder function
void postorder(RB_TREE *root)
{
	if(root != NULL){
		postorder(root->left);
		postorder(root -> right);
		printf("%d\t", root -> data);							///display node data
		root->color?printf("RED\n"):printf("BLACK\n");			///display color of node
	}
}
