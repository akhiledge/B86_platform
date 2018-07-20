/*
 * @brief Function definition to right rotate from parent
 * @param parent address
 * @return root address
 * */
bst_t *right_rotate_from_parent(bst_t **parent)
{
    ///Swapping addresses
    (*parent)->left->right = *parent;
    (*parent)->left->prev = (*parent)->prev;

    (*parent)->prev->right = (*parent)->left;
    (*parent)->left = NULL;
    (*parent)->prev = (*parent)->prev->right;

    ///Function call to left rotate from grand parent
    return left_rotate_from_gp(&(*parent)->prev);
}
