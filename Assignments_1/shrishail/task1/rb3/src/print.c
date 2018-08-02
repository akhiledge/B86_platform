void print(rbtree *root)                                                     
{                                                                               
	inorder(root);                                                              
}                                                                               

///Inorder function(Recursive)                                                  
void inorder(rbtree *root)                                                     
{                                                                               
	if(root != NULL)
	{                                                           
		inorder(root->left);                                                    
		printf("%d\t", root -> val);                                           
		if(root->color)
		{
		printf("RED\n");
		}
		else
		{
		printf("BLACK\n");
		}                        
		inorder(root -> right);                                                 
	}                                                                           
}                    
