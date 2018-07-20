/**
 * @brief Function definition to left rotate from grand parent
 * @param parent node address
 * */
bst_t *left_rotate_from_gp(bst_t **parent)
{
    bst_t *temp;

    ///Swapping addresses
    (*parent) -> left = (*parent) -> prev;
    temp = (*parent) -> prev -> prev;

    if(temp != NULL)
    {
        if(temp -> left  == (*parent) -> prev)
            (*parent) -> prev -> prev -> left = *parent;
        else
            (*parent) -> prev -> prev -> right = *parent;
    }

    (*parent) -> prev -> prev = *parent;
    (*parent) -> prev -> right = NULL;
    (*parent) -> prev = temp;

    ///Changing colors of parent and grand parent
    (*parent) -> color = ((*parent) -> color) ^ 1;
    (*parent) -> left -> color = ((*parent) -> left -> color) ^ 1;

    ///Finding root
    return find_root(*parent);
}
