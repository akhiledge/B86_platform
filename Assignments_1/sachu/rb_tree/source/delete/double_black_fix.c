/**
 * @brief Function definition to fix double black issue
 * @param d_node is a pointer storing address of node to be deleted
 * @param root stores address of root of tree
 * */
void double_black_fix(bst_t **d_node, bst_t **root)
{

    ///Node is a right child
    if((*d_node) -> prev -> right == (*d_node))
    {
        bst_t *ttemp = (*d_node) -> prev->left;

        ///Sibling red with black children
        if((*d_node) -> prev -> left -> color == RED)
        {
            bst_t *temp = (*d_node) -> prev -> left -> right;
            temp -> color = RED;

            ///Right rotating
            *root = right_rotate_from_gp(&ttemp);

            (*d_node) -> prev -> color = BLACK;
            (*d_node) -> prev -> left = temp;
            temp->prev = (*d_node) -> prev;

            temp -> prev -> right = NULL;
            free(*d_node);
        }

        ///Sibling black case
        else
        {
            bst_t *temp = (*d_node) -> prev -> left;

            if((*d_node) -> prev -> color == BLACK) ///Parent of node  Black case
            {

                ///Sub case - Black Sibling with no children
                if(temp -> left == NULL && temp -> right == NULL)
                {
                    ///Parent root case 
                    if((*d_node) -> prev->prev == NULL)
                    {
                        temp -> color = RED;
                        temp -> prev->right = NULL;
                        free(*d_node);
                    }
                    else
                    {
                        ///Function call to fix black height
                        black_height_fix(d_node, root);
                    }
                }

                ///Sub case - Right red child only for black sibling
                else if(temp -> left == NULL)   
                {
                    *root = left_rotate_from_parent(&temp); 

                    temp -> right = NULL;
                    (*d_node) -> prev -> color = BLACK;
                    (*d_node) -> prev -> right = NULL;
                    free(*d_node);
                }

                ///Sub case - Left red child only for black sibling 
                else if(temp -> right == NULL) 
                {
                    *root = right_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> left->color = BLACK;
                    temp -> right -> color = BLACK;
                    (*d_node) -> prev->right = NULL;
                    free(*d_node);
                }

                ///Sub case - Black Sibling with two children
                else
                {
                    bst_t *new = temp -> right;
                    temp -> left -> color = BLACK;

                    *root = right_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> right -> right = NULL;
                    temp -> right -> left = new;
                    new -> prev = temp -> right;
                    temp -> right -> color = BLACK;
                    free(*d_node);
                }
            }

            ///Parent of node Red case
            else    
            {
                
                ///Sub case - Sibling with no children
                if(temp -> left == NULL && temp -> right == NULL)
                {
                    temp -> color = RED;
                    (*d_node) -> prev -> color = BLACK;
                    (*d_node) -> prev -> right = NULL;
                    free(*d_node);
                }

                ///Sub case - Left red child only for sibling
                else if(temp -> right == NULL)
                {
                    *root = right_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> right -> color = RED;
                    (*d_node) -> prev -> right = NULL;
                    free(*d_node);
                }

                ///Sub case - Right red child only for sibling
                else if(temp -> left == NULL)
                {
                    *root = left_rotate_from_parent(&temp);
                    temp -> color = RED;
                    (*d_node) -> prev -> color = RED;
                    (*d_node) -> prev -> right = NULL;
                    free(*d_node);
                }

                ///Sub case - Sibling with two children
                else
                {
                    bst_t *new = temp -> right;
                    temp -> left->color = BLACK;

                    *root = right_rotate_from_gp(&temp);

                    temp -> right -> right = NULL;
                    temp -> right -> left = new;
                    new -> prev = temp -> right;
                    free(*d_node);
                }
            }
        }
    }

    ///Node is a left child
    else
    {
        
        bst_t *ttemp=(*d_node) -> prev -> right;

        ///Sibling red with black children
        if((*d_node) -> prev -> right -> color == RED) 
        {
            bst_t *temp = (*d_node) -> prev -> right -> left;
            temp -> color = RED;

            *root = left_rotate_from_gp(&ttemp);

            (*d_node) -> prev -> color = BLACK;
            (*d_node) -> prev -> right = temp;
            temp -> prev = (*d_node) -> prev;
            temp -> prev -> left = NULL;
            free(*d_node);
        }

        else ///Sibling black case
        {
            
            bst_t *temp = (*d_node) -> prev -> right;

            ///Sub case - Parent node Black
            if((*d_node) -> prev -> color == BLACK) 
            {
                ///Sub case - Black Sibling with no children
                if(temp -> left == NULL && temp -> right == NULL)
                {
                    if((*d_node) -> prev -> prev == NULL)
                    {
                        temp -> color = RED;
                        temp -> prev->left = NULL;
                        free(*d_node);
                    }
                    else
                    {
                        black_height_fix(d_node, root);
                    }
                }

                ///Sub case - Left red child only for black sibling
                else if(temp -> right == NULL)   
                {
                    *root = right_rotate_from_parent(&temp);

                    temp -> left = NULL;
                    (*d_node) -> prev->color = BLACK;
                    (*d_node) -> prev->left = NULL;
                    free(*d_node);
                }

                ///Sub case - Right red child only for black sibling
                else if(temp -> left == NULL) 
                {
                    *root = left_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> left -> color = BLACK;
                    temp -> right -> color = BLACK;
                    (*d_node) -> prev -> left = NULL;
                    free(*d_node);
                }

                ///Sub case - Black Sibling with two children
                else    
                {
                    bst_t *new = temp -> left;

                    *root = left_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> left -> color = BLACK;
                    temp -> right -> color = BLACK;
                    temp -> left -> left = NULL;
                    temp -> left -> right = new;
                    new->prev = temp->left;
                    free(*d_node);
                }
            }

            ///Case - Parent node red
            else    
            {
                
                ///Sub case - Black Sibling with no children
                if(temp -> left == NULL && temp -> right == NULL)
                {
                    temp -> color = RED;
                    (*d_node) -> prev -> color = BLACK;
                    (*d_node) -> prev -> left = NULL;
                    free(*d_node);
                }

                ///Sub case - Black Sibling with right child
                else if(temp -> left == NULL)
                {
                    *root = left_rotate_from_gp(&temp);

                    temp -> color = BLACK;
                    temp -> left -> color = RED;
                    (*d_node) -> prev -> left = NULL;
                    free(*d_node);
                }

                ///Sub case - Black Sibling with left child
                else if(temp -> right == NULL)
                {
                    *root = right_rotate_from_parent(&temp);

                    temp -> color = RED;
                    (*d_node) -> prev -> color = RED;
                    (*d_node) -> prev -> left = NULL;
                    free(*d_node);
                }

                ///Sub case - Black Sibling with two children
                else
                {
                    bst_t *new = temp -> left;
                    temp -> right -> color = BLACK;

                    *root = left_rotate_from_gp(&temp);

                    temp -> left -> left = NULL;
                    temp -> left -> right = new;
                    new -> prev = temp -> right;
                    free(*d_node);
                }
            }
        }
    }
}
