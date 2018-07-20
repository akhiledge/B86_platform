node *left_rotate(node  *pivot){
    node *temp = NULL;
    temp = (pivot->right);
    (pivot->right) = (temp->left);
    (temp->left) = (pivot);
    return temp;
}
