/**
 * @brief Function to delete a particular node from tree
 * **/

bst_t* delete_element(bst_t *root)
{
    int value;
    char str[SIZE];

    if(root == NULL)             ///Checking for empty tree
    {
        printf("Tree already empty\n");
        return root;
    }

    ///Prompt for element to be deleted
    printf("Enter the element to be deleted\n");
    fgets(str, SIZE, stdin);
    __fpurge(stdin);
    value = atoi(str);

    root = delete_node_val(root, value);  ///Function call to delete node
    return root;
}

///Function definition to delete a node
bst_t *delete_node_val(bst_t *root, int value)
{
    if(root == NULL)
        printf("Element not found\n");

    ///Recursive function call to find node to be deleted
    else if(root->data > value)
        root->left = delete_node_val(root->left, value);
    else if(root->data < value)
        root->right = delete_node_val(root->right, value);

    else
    {
        ///If node is a leaf node
        if(root->left == NULL && root->right == NULL)
        {
            if(root->prev == NULL) ///Single node case-No child
            {
                free(root);
                root = NULL;
            }
            else
            {
                if(root->color == RED)   ///Red node delete
                {
                    bst_t *new = root;
                    root = NULL;
                    if(new->prev->left == new)
                        new->prev->left = NULL;
                    else
                        new->prev->right = NULL;
                    free(new);
                }
                else            ///Black node delete - Double black problem
                {
                    bst_t *ret = root;
                    if(root->prev->right == root) ///Right child delete
                    {
                        if(root->prev->left->color == BLACK) ///Node black
                        {
                            bst_t *ttemp = root->prev->prev;
                            root->prev->prev = root->prev->left;
                            root->prev->right = NULL;
                            root->prev->left->prev = ttemp;
                            ttemp = root->prev->left->right;
                            root->prev->left->right = root->prev;
                            root->prev->left = ttemp;
                            root->prev->color = BLACK;
                            root->prev->prev->left->color = BLACK;
                            //root->prev->right = NULL;
                            root = NULL;
                        }
                        else
                        {
                            bst_t *ttemp = root->prev->prev; ///Node red
                            root->prev->prev = root->prev->left;
                            root->prev->right = NULL;
                            root->prev->left->prev = ttemp;
                            ttemp = root->prev->left->right;
                            root->prev->left->right = root->prev;
                            root->prev->left = ttemp;

                            if(root->prev->left != NULL)
                                root->prev->left->color = RED;
                            else
                                root->prev->color = BLACK;

                            root->prev->prev->left->color = BLACK;
                            root->prev->prev->color = BLACK;
                            root = NULL;
                        }
                    }
                    else                    ///Left child case
                    {
                        if(root->prev->right->color == BLACK) ///Black node
                        {
                            bst_t *ttemp = root->prev->prev;
                            root->prev->prev = root->prev->right;
                            root->prev->left = NULL;
                            root->prev->right->prev = ttemp;
                            ttemp = root->prev->right->left;
                            root->prev->right->left = root->prev;
                            root->prev->right = ttemp;
                            root->prev->color = BLACK;
                            root->prev->prev->right->color = BLACK;
                            root = NULL;
                            //root->prev->left = NULL;
                            root = NULL;
                        }
                        else                               ///Red node
                        {
                            bst_t *ttemp = root->prev->prev; 
                            root->prev->prev = root->prev->right;
                            root->prev->left = NULL;
                            root->prev->right->prev = ttemp;
                            ttemp = root->prev->right->left;
                            root->prev->right->left = root->prev;
                            root->prev->right = ttemp;
                            root->prev->right->color = RED;
                            root->prev->prev->right->color = BLACK;
                            root = NULL;
                        }
                    }
                    free(ret);
                }
            }
        }
        ///Node has a right child case
        else if(root->left == NULL)   ///Root is black and only right child is red
        {
            bst_t *ret = root;
            root->right->prev = root->prev;
            root = root->right;
            root->color = BLACK;
            free(ret);
        }
        ///Node has a left child
        else if(root->right == NULL)  ///Root is black and only left child is red
        {
            bst_t *ret = root;
            root->left->prev = root->prev;
            root = root->left;
            root->color = BLACK;
            free(ret);
        }
        ///Two child case
        else 
        {

            ///Finding successor(min element from the right child)
            bst_t *temp = find_min_element(root->right);
            root->data = temp->data;
            root->right = delete_node_val(root->right, temp->data);
        }
    }
    return root;
}        
