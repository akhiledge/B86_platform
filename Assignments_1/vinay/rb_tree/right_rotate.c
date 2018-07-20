node *right_rotate(node  *pivot){
    node *temp = NULL;
    temp = (pivot->left);
    (pivot->left) = (temp->right);
    (temp->right) = (pivot);
    return temp;
}
