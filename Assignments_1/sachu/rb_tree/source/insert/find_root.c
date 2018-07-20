/**
 * @brief Function to find root of red black tree
 * */
bst_t *find_root(bst_t *root)
{
    while(root->prev != NULL) ///Looping back till root
        root = root->prev;
    return root;
}
