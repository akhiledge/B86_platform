bool preorder (node *subtree_root){
    if (NULL != subtree_root){
        printf (" %d(%s)", (subtree_root->value), (subtree_root->color)?"black":"red"); 
        preorder (subtree_root->left);
        preorder (subtree_root->right);
    }
    return;    
}
