bool postorder (node *subtree_root){
    if (NULL != subtree_root){
        postorder (subtree_root->left);
        postorder (subtree_root->right);
        printf (" %d(%s)", (subtree_root->value), (subtree_root->color)?"black":"red"); 
    }
    return;    
}
