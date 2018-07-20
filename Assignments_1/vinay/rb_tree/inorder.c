bool inorder (node *subtree_root){
    if (NULL != subtree_root){
        inorder (subtree_root->left);
        printf (" %d(%s)", (subtree_root->value), (subtree_root->color)?"black":"red"); 
        inorder (subtree_root->right);
    }
    return true;    
}
