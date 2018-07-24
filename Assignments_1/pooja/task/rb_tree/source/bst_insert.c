///Function to insert node and calls modify function
RB_TREE *insert_node(RB_TREE *root, int data)
{
	RB_TREE *temp = NULL;				/*!node to traverse tree*/
	RB_TREE *prev = NULL;				/*!node to keep track of previous node*/
	RB_TREE *new = NULL;				/*!new nodwe inserted*/
	int left = 0;
	int right = 0;
	if(root == NULL){					///if tree is empty, insert node which becomes root
		root = create_node(root,data);	///create_node function call
		root->color = BLACK;			///root node has to be black
		return root;					///@return root
	}

	temp = root;
	while((temp != NULL) && ((temp->data > data) || (temp->data < data))){	///traversing the tree
		if(temp->data > data){
			prev = temp;
			left = 1;
			right = 0;
			temp = temp->left;
		}
		else{
			prev = temp;
			left = 0;
			right = 1;
			temp = temp->right;
		}
	}

	if(temp == NULL){
		if(left){
			new = create_node(prev, data);
			prev->left = new;
		}
		else if(right){ 
			new = create_node(prev, data);
			prev->right = new;
		}
		printf("Node inserted\n");
		root = modify_node(root, new);
		return root;
	}
				else{										///if duplicate is alreday present
				printf("Sorry!! No duplicates allowed\n");
				return root;
				}	
				}
