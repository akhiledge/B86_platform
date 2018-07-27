/**
 * @brief Function to find uncle color
 * @param parent node address
 * @return Returns color of uncle node
 * */
int check_uncle(bst_t **parent)
{
    if((*parent) -> prev -> right == (*parent))  ///Parentright child
    {
        if((*parent) -> prev -> left != NULL)     
            return (*parent) -> prev -> left -> color;
        return BLACK;
    }
    else                                    ///Parent is left child
    {
        if((*parent) -> prev -> right != NULL)
            return (*parent) -> prev -> right -> color;
        return BLACK;
    }
}


