/**
 * @brief Function definition to insert new node
 * @param root is a double pointer storing root of tree
 * @param value is integer storing new element
 * **/

void insert_element(bst_t **root, int value)
{
    bst_t *ptr = *root;  /*! ptr is a temporary pointer of type bst_t */
    bst_t *prev = NULL;  /*! prev is a pointer of type bst_t */
    if(*root == NULL)
    {
        *root = create_node(*root, value);  ///Tree empty case
        return;
    }

    while(1)         ///Looping till insert location
    {
        prev = ptr;  ///prev stores parent address

        if(value < ptr -> data)  
            ptr = ptr -> left;
        else if(value > ptr->data)
            ptr = ptr -> right;
        else
        {
            printf("Equal nodes are not possible\n");
            return;
        }

        if(ptr == NULL)
            break;
    }

    if(value < prev -> data)                     ///Inserting as left node
    {
        prev -> left = create_node(prev, value);  ///Function call for create
        *root = check_parent(root, &prev, prev -> left); ///Function call to check parent
    }
    else                                      ///Inserting as right node
    {
        prev -> right = create_node(prev, value);
        *root = check_parent(root, &prev, prev->right); ///Function call to check parent
    }
}
