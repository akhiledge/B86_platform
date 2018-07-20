int main()                                                                      
{                                                                               
	char *str = NULL;                                                           
	rbtree *root = NULL;                 

	str = (char *) malloc(MAX);
	if(str == NULL)
	{
		printf("failed to allocate memory\n");
		exit(0);
	}                                         
	int op;
	int val;              
	while(1)
{                                                                   
		printf("Enter choice\n");                                               
		printf("1.insert node into tree\n2.display the nodes\n3.exit\n");                        
		fgets(str, MAX, stdin);                                                 
		assert(str);                                                            
		op = atoi(str);                             
		switch(op)
		{
			case 1: printf("input a number\n");                 
				fgets(str, MAX, stdin);                                     
				val = atoi(str);                                           
				root = insert(root, val);                             
				break;                                                      
			case 2: print(root);                              
				break;                                                      
			case 3: exit(0);                                                    
			default: printf("Invalid argument! check again\n");                                
		}                                                                       
	}                                                                           
}                                                                               
                                 
