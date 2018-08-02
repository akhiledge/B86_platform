node *sibling (node *child, node *parent){
    return ((parent->right) == child)?(parent->left):(parent->right);
}
