rbtree *alternode(rbtree *root, rbtree *newnode)                               
{                                                                               
	rbtree *parent = NULL;                                 
	rbtree *grandparent = NULL;                            
	rbtree *uncle = NULL;                                     
	int index = 0;                                                              
	if(newnode->parent != root)
	{                                                  
		parent = newnode->parent;                                                   
		grandparent = newnode->parent->parent;                                      
		if(parent->color)
		{
			if(grandparent -> left != parent)          
				uncle = grandparent->left;                                      
			else                                                                
				uncle = grandparent->right;                                     

			if(uncle == NULL || (uncle->color == BLACK))
			{   

				if((grandparent->left == parent) && (parent->left == newnode))
					root=right_rotategp(root,grandparent);
				else if((grandparent->left == parent) && (parent->left!=newnode)){
					left_rotate(parent);
					root=right_rotategp(root,grandparent);
				}
				else if((grandparent->left != parent) && (parent->left!=newnode))
				{
					root=left_rotategp(root,grandparent);
				}
				else if((grandparent->left != parent) && (parent->left == newnode))
				{
					right_rotate(parent);
					root=left_rotategp(root,grandparent);
				}
				return root;
			}
			else
			{                                       
				parent->color = BLACK;                                          
				uncle->color = BLACK;                                           
				if(grandparent != root)                                         
					grandparent->color = RED;                                   
				return root;                                                    
			}                                                                   
		}                                                                       
	}                                                                           
	return root;                                                                
}                                                                               
rbtree *right_rotategp(rbtree *root, rbtree *grandparent)                   
{                                                                               
	rbtree *parent = grandparent -> left;                                      
	grandparent->left = parent->right;                                          
	parent->right = grandparent;                                                
	if((grandparent->parent != NULL) && (grandparent->parent->left == grandparent))
		grandparent->parent->left = parent;                                     
	else                                                                        
		grandparent->parent->right = parent;                                    
	parent->parent = grandparent->parent;                                       
	grandparent->parent = parent;                                               
	grandparent->color = RED;                                                   
	parent->color = BLACK;                                                      
	if(parent->parent == NULL)
	{                                                 
		root = parent;    
		return root;                                                            
	}                                                                           
	return root;                                                                
}                                                                               
rbtree *left_rotategp(rbtree *root, rbtree *grandparent)                    
{                                                                               
	rbtree *parent = grandparent -> right;                                     
	grandparent->right = parent->left;                                          
	parent-> left = grandparent;                                                
	if((grandparent->parent != NULL) && (grandparent->parent->left == grandparent))
		grandparent->parent->left = parent;                                     
	else                                                                        
		grandparent->parent->right = parent;                                    
	parent->parent = grandparent->parent;                                       
	grandparent->parent = parent;                                               
	grandparent->color = RED;                                                   
	parent->color = BLACK;                                                      
	if(parent->parent == NULL)
	{                                                 
		root = parent;                                                          
		return root;                                                            
	}                                                                           
	parent->parent->right = parent;           
	return root;                                                                
}                                                                               
void right_rotate(rbtree *parent)                                              
{                                                                               
	rbtree *child = parent->left;                                             
	parent->parent->right = child;                                              
	child->parent = parent->parent;                                             
	parent->parent = child;                                                     
	if(parent-> right != NULL)                                                  
	parent->right->parent = child;                                          
	child->left = parent->right;                                                
	child->right = parent;                                                      
	parent->left = NULL;                                                        
	parent->right = NULL;                                                       
}
 void left_rotate(rbtree *parent)                                               
{                                                                               
	rbtree *child = parent ->right;                                            
	parent->parent->left = child;                                               
	child->parent = parent->parent;                                             
	parent->parent = child;                                                     
	if(parent->left != NULL)                                                    
	parent->left->parent = child;                                           
	child->right = parent->left;                                                
	child->left = parent;                                                       
	parent->left = NULL;                                                        
	parent->right = NULL;                                                       
}        
