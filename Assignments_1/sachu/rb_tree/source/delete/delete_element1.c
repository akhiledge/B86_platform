/**
 *  * @brief Function to delete a particular node from tree
 *  * **/

void delete_element(bst_t **root)
{
    int value;
    char str[SIZE];

    if(root == NULL)             ///Checking for empty tree
    {
        printf("Tree already empty\n");
        return;
    }

    ///Prompt for element to be deleted
    printf("Enter the element to be deleted\n");
    fgets(str, SIZE, stdin);
    __fpurge(stdin);
    value = atoi(str);

    delete_node_val(root, value);  ///Function call to delete node
}
void delete_node_value(bst_t **root, int value)
{
    bst_t ptr = *root;
    bst_t prev = NULL;
    if( *root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }
    while(1)
    {
        prev = ptr;
        if(ptr->data > value)
            ptr = ptr->left;
        else if(ptr->data < value)
            ptr = ptr->right;
        if(ptr == NULL)
        {
            printf("Element not found\n");
            return;
        }
        if(ptr->data == value)
        {
            operation_delete(root,ptr);
            return;
        }
    }
}
void operation_delete(bst_t **root, bst_t *d_node)
{
    if(d_node->left == NULL && d_node->right == NULL)
    {
        if(d_node->color == RED)
        {
            if(d_node->prev->left == d_node)
                d_node->prev->left = NULL;
            else
                d_node->prev->right = NULL;
            free(d_node);
        }
        else
        {

        }
    }
    else if(d_node->left == NULL)
    {
        d_node->data = d_node->right->data;
        free(d_node->right);
        d_node->right = NULL;
    }
    else if(d_node->right == NULL)
    {
        d_node->data = d_node->left->data;
        free(d_node->left);
        d_node->left = NULL;
    }
    else
    {
        bst_t *temp = find_min_element(d_node->right);
        d_node->data = temp->data;
        operation_delete(root, temp);
    }
