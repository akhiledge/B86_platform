/*
 * @brief Function definition for creating node
 * @param parent address
 * @param value stores the new element
 * @return Created node address
 * */
bst_t *create_node(bst_t *parent, int value)
{
    bst_t *new =(bst_t *) malloc(sizeof(bst_t)); ///Dynamic allocation of memory
    assert(new);

    ///Assigning addresses and inserting value
    new->prev = parent;
    new->data = value;
    new->color = 0;
    new->left = NULL;
    new->right = NULL;

    ///Root node
    if(parent == NULL)
        new->color = 1;

    return new;
}
