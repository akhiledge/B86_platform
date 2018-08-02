/**
 * @brief To find the minimum value in the tree
 * */

void find_min(bst_t *root)
{
    ///Checking for empty tree
    if(root == NULL)
    {
        printf("Tree already empty\n");
        return;
    }

    bst_t *temp = find_min_element(root);   ///Function call to find minimum
    printf("Minimum value in tree is %d\n", temp -> data);
}

bst_t* find_min_element(bst_t *root)
{
    if(root -> left != NULL)                 ///Recursively moving to left node
        return find_min_element(root -> left);

    return root;
}
