/**
 * @brief Searching for any element present in tree or not
 * @param root stores root of tree
 * */
void search_tree(bst_t *root)
{
    int value;
    char str[SIZE];

    ///Empty tree case
    if(root == NULL)
    {
        printf("Tree already empty\n");
        return;
    }

    ///Prompt for search key
    do
    {
        printf("Enter value to be searched\n");
        fgets(str, SIZE, stdin);
        __fpurge(stdin);

        value = my_atoi(str);
    }while(value == INVALID);

    ///Function call for searching
    root = search_element(root, value);

    (root == NULL)? printf("Value not found\n"): printf("%d Found : Color = %s\n", root ->data, COLOR);
}

///Function definition for search
bst_t* search_element(bst_t *root, int value)
{
    if(root != NULL)
    {
        ///Recursive search call till value matches or NULL occurs
        if(root -> data > value)
            return search_element(root -> left, value);

        else if(root -> data < value)
            return search_element(root -> right, value);

        else
            return root;
    }
    return NULL;
}
