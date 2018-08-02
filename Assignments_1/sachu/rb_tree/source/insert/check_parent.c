/**
 *@brief Function to check parent color
 * @param root for storing tree root address
 * @param parent for storing parent node address
 * @param child for storing child node address
 * @return Returns root of tree
 * */
bst_t *check_parent(bst_t **root, bst_t **parent, bst_t *child)
{
    bst_t *ret;
    int uncle_clr;               /*! uncle_clr for storing uncle color */
    if(((*parent) -> color) == BLACK)  ///Parent black case- Balanced tree
        return *root;

    uncle_clr = check_uncle(parent); ///Function call check_uncle

    if(uncle_clr == RED)               ///Uncle -Red
    {
        ///Swapping colors of parent, grand parent and uncle
        (*parent) -> prev -> left -> color ^= MAX;  
        (*parent) -> prev -> right -> color ^= MAX;

        if((*parent) -> prev -> prev != NULL)
            (*parent) -> prev -> color ^= MAX;

        return *root;
    }

    else ///Unbalanced case-Uncle color- Black
    { 
        if((*parent) -> prev -> left == *parent)  ///Parent is left child
        {
            if((*parent) -> left == child)      ///Child also left(left-left)
            {
                ret = right_rotate_from_gp(parent); ///Function call to right rotate from grand parent
            }
            else                              ///Child right(left-right)
            {
                ret = left_rotate_from_parent(parent);///Function call to left rotate from parent
            }
        }
        else                                 ///Parent is right child
        {
            if((*parent) -> right == child)    ///Child also right(right-right)
            {
                ret = left_rotate_from_gp(parent); ///Function call to left rotate from grand parent
            }
            else                            ///Child is left(right-left)
            {
                ret = right_rotate_from_parent(parent); ///Function call to right rotate from parent
            }
        }
        return ret;  ///Returning root
    }
}
