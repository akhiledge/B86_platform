/**
 * @brief Function definition to right rotate from grand parent
 * @param parent node address
 * @return Returns root of tree
 * */
bst_t *right_rotate_from_gp(bst_t **parent)
{
    bst_t *temp;

    ///Swapping addressses
    (*parent) -> right = (*parent) -> prev;
    temp = (*parent) -> prev -> prev;

    if(temp != NULL)
    {
        if(temp -> left  == (*parent) -> prev)
            (*parent) -> prev -> prev -> left = *parent;
        else
            (*parent) -> prev -> prev -> right = *parent;
    }

    (*parent) -> prev -> prev = *parent;
    (*parent) -> prev -> left = NULL;
    (*parent) -> prev = temp;

    ///Changing colors of parent and grand parent
    (*parent) -> color = ((*parent) -> color) ^ MAX;
    (*parent) -> right -> color = ((*parent) -> right -> color) ^ MAX;

    ///Finding root
    return find_root(*parent);
}
