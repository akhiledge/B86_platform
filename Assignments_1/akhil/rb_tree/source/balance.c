/*******
 *rotate at a node
 ********/
extern node *root;
void balance(node *great_grandparent, node *grandparent, node *parent, enum side child_pos){
    node *siblings = NULL;
    bool color;
    if (BLACK == (parent->color))
        return;
    else{
        if (NULL != grandparent)
            siblings = sibling (parent, grandparent);
        if (NULL == siblings)
            color = BLACK;
        else 
            color = siblings->color;
        if (RED == color){
            (grandparent->color) = !(grandparent->color);
            (parent->color) = !(parent->color);
            (siblings->color) = !(siblings->color);
        }
        else{
            switch (child_pos){
                case leftright:
                    (grandparent->left) = left_rotate (parent);
                case leftleft:{
                                  if (NULL != great_grandparent){
                                      grandparent = (great_grandparent->left);
                                      parent = (grandparent->left);
                                      (great_grandparent->left) = right_rotate (grandparent);
                                  }
                                  else{
                                      grandparent = parent;
                                      parent = (grandparent->left);
                                      root = right_rotate (grandparent);
                                  }
                                  (parent->color) = !(parent->color);
                                  (grandparent->color) = !(grandparent->color);
                                  break;
                              }
                case rightleft:
                              (grandparent->right) = right_rotate (parent);

                case rightright:{
                                    if (NULL != great_grandparent){
                                        grandparent = (great_grandparent->right);
                                        parent = (grandparent->right);
                                        (great_grandparent->right) = left_rotate (grandparent);
                                    }
                                    else{
                                        grandparent = parent;
                                        parent = (grandparent->right);
                                        root = left_rotate (grandparent);
                                    }
                                    (parent->color) = !(parent->color);
                                    (parent->left->color) = !(parent->left->color);
                                    break;
                                }
            }
        }
    }
    return ; 
}
