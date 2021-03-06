/** To modify the RB Tree*/
RB_TREE *modify_node(RB_TREE *root, int data)
{
	RB_TREE *traverse = NULL;								///variable to traverse
	RB_TREE *parent = NULL;									///parent node
	RB_TREE *grandparent = NULL;							///grandparent node
	RB_TREE *uncle = NULL;									///uncle node

	int index = 0;
	int LEFT1 = 0;
	int RIGHT1 = 0;
	int LEFT2 = 0;
	int RIGHT2 = 0;

	if((root->left == NULL) && (root->right == NULL)){			///root has to be black
	root->color = BLACK;
	return root;
	}

	traverse = root;
	while((traverse -> data > data) || (traverse->data < data)){	///for traversing the tree
		if(data > traverse ->data)
		traverse = traverse->right;
		else
		traverse = traverse->left;
		index++;
	}

	if(index > 1) {													///modify after height > 1
		parent = traverse->parent;
		grandparent = traverse->parent->parent;
		if(parent->color){						///if parent is red, check uncle
			if(grandparent -> left != parent)			///get uncle nodes address
			uncle = grandparent->left;
			else
			uncle = grandparent->right;
			
			if(uncle == NULL || (uncle->color == BLACK)){	///if parent is red & uncle is black
				printf("UNcle is black\n");
				if(grandparent -> left == parent)			///To get the details about 4 cases
				LEFT1 = 1;
				else
				RIGHT1 = 1;
				if(parent->left == traverse)
				LEFT2 = 1;
				else
				RIGHT2 =1;

				if(LEFT1 & LEFT2)							///Left Left case
				root = right_rotate_gp(root, grandparent);
				else if(LEFT1 & RIGHT2){					///Left Right case
				left_rotate(parent);
				root = right_rotate_gp(root, grandparent);
				}
				else if(RIGHT1 & RIGHT2){					///Right Right case
					root = left_rotate_gp(root, grandparent);
				}
				else if(RIGHT1 & LEFT2){										///Right left case
					right_rotate(parent);
					root = left_rotate_gp(root, grandparent);
				}
		return root;		
		}
			else{											///if parent is red, uncle is red(change colors of parent,uncle and grandparent nodes
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
///Function to right rotate grandparent node
RB_TREE *right_rotate_gp(RB_TREE *root, RB_TREE *grandparent)
{
	RB_TREE *parent = grandparent -> left;
	grandparent->left = parent->right;
	parent->right = grandparent;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;	
	grandparent->color = RED;

	if(parent->parent == NULL){
		root = parent;
		parent->color = BLACK;
	}
	return root;
}
///Function definition to left rotate parent node
void left_rotate(RB_TREE *parent)
{
	RB_TREE *child = parent ->right;
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
/// Function definition to left rotate grandparent node
RB_TREE *left_rotate_gp(RB_TREE *root, RB_TREE *grandparent)
{
	RB_TREE *parent = grandparent -> right;
	grandparent->right = parent->left;
	parent-> left = grandparent;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;	
	grandparent->color = RED;

	if(parent->parent == NULL){
		root = parent;
		parent->color = BLACK;
	}
	return root;
}
///Function definition to right rotate parent node
void right_rotate(RB_TREE *parent)
{
	printf("IN left rotate\n");
	RB_TREE *child = parent ->left;
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
