/*******
 *insert function
 ********/ 
extern node *root;
bool insert (int num){
    node *current = NULL;
    node *parent = NULL, *grandparent = NULL;
    node *great_grandparent = NULL;
    enum side child_pos;
    current = root;
    if (NULL == current){
        current = allocate_memory (BUF_SIZE);
        root = current;
        (current->value) = num;
    }
    else{
        while (NULL != current){
            great_grandparent = grandparent;
            grandparent = parent;
            parent = current;
            if ((current->value) < num){
                current = (current->right);
            }
            else if ((current->value) == num){
                return false;
            }
            else{
                current = (current->left);
            }
        }
        current = allocate_memory (BUF_SIZE);
        (current->value) = num;
        if ((parent->value) < num){
            (parent->right) = current;
            child_pos = 1;
        }
        else{
            (parent->left) = current;
            child_pos = 0;
        }
        if (NULL != grandparent){
            child_pos += (parent == (grandparent->left))?1:3;
            balance (great_grandparent, grandparent, parent, child_pos);
        }
    }

    (root->color) = BLACK;
    return true; 
}
