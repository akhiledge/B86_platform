/**
 * @brief Function definition to left rotate from parent
 * @param parent node address
 * @return Returns root of tree
 * */
bst_t *left_rotate_from_parent(bst_t **parent)
{

    ///Swapping addresses
    (*parent) -> right -> left = *parent;
    (*parent) -> right -> prev = (*parent) -> prev;

    (*parent) -> prev -> left = (*parent) -> right;
    (*parent) -> right = NULL;
    (*parent) -> prev = (*parent) -> prev -> left;
    
    ///Calling right rotate function
    return right_rotate_from_gp(&(*parent) -> prev);  
}
