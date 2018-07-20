rbtree *insert(rbtree *root, int val)                                   
{                                                                               
	rbtree *ptr = NULL;                  
	rbtree *prev = NULL;               
	rbtree *newnode = NULL;                            
	int left;                                                               
	int right;                                                              
	if(root == NULL){                   
		root = create(root,val);         
		root->color = BLACK;                      
		return root;                                     
	}                                                                           

	ptr = root;                                                                
	while((ptr != NULL) && ((ptr->val > val) || (ptr-> val < val)))
	{
		if(ptr-> val > val)
		{                                                  
			prev = ptr;                                                        
			left = 1;                                                           
			right = 0;                                                          
			ptr = ptr->left;                                                  
		}                                                                       
		else
		{                                                                   
			prev = ptr;                                                        
			left = 0;                                                           
			right = 1;                                                          
			ptr = ptr->right;                                                 
		}                                                                       
	}                                                                           

	if(ptr == NULL)
	{                                                           
		if(left)
		{                                                               
			newnode = create(prev, val);                                      
			prev->left = newnode;                                                   
		}                                                                       
		else if(right)
		{                                                         
			newnode = create(prev, val);                                      
			prev->right = newnode;                                                  
		}                                                                       
		root = alternode(root, newnode);                                          
		return root;                                                            
	}                                                                           
}                                                               
                        
