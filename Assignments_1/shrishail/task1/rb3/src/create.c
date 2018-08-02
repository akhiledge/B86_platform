rbtree *create(rbtree *root, int val)                                   
{                                                                               
	rbtree *newnode = NULL;                        
	newnode = (rbtree *)malloc(sizeof(rbtree));                                   
	newnode-> val = val;                                                         
	newnode->left = NULL;                                                           
	newnode->right = NULL;                                                          
	newnode->color = RED;                                                           
	newnode->parent = root;                                                         
	return newnode;                                                                 
}                                                                               
            
