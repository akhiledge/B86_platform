/**
 * \file insert.c
 * \brief insert an element in the tree
 * \param num value to be inserted
 **/ 
extern node *root;                          /**< pointer to the root of tree*/ 

bool insert (int num){

    node *current = NULL;                   /**< pointer to the current node in
                                              tree*/ 
    node *parent = NULL;                    /**< pointer to parent of current 
                                              node*/ 
    node *grandparent = NULL;               /**< pointer to grandparent of 
                                              current node*/ 
    node *great_grandparent = NULL;         /**< pointer to great_grandparent 
                                              of current node*/ 
    enum side child_pos;                    /**< position of node inserted*/ 

    current = root;                          

    if (NULL == current){                   /** tree is empty*/ 
        current = allocate_memory (BUF_SIZE);
        root = current;
        (current->value) = num;
    }
    else{                                   /** tree is not empty*/ 
        while (NULL != current){            /** traverse till the position of 
                                              new element is found*/ 
            great_grandparent = grandparent;
            grandparent = parent;
            parent = current;
            if ((current->value) < num){    /** traverse to right if value to 
                                              be inserted is greater than value
                                              at current node*/ 
                current = (current->right);
            }
            else if ((current->value) == num){/** value already inserted into 
                                                tree, return */ 
                return false;
            }
            else{                           /** traverse left if value to be 
                                              added is less than value at 
                                              current node*/ 
                current = (current->left);
            }
        }
        current = allocate_memory (BUF_SIZE);
        (current->value) = num;

        if ((parent->value) < num){         /** child position with respect to 
                                              parent*/ 
            (parent->right) = current;
            child_pos = 1;                  /** 1 if right*/ 
        }
        else{
            (parent->left) = current;
            child_pos = 0;                  /** 0 if left*/ 
        }

        if (NULL != grandparent){
            child_pos += (parent == (grandparent->left))?1:3;/** child position
                                                              wrt grandparent*/ 
            balance (great_grandparent, grandparent, parent, child_pos);/** 
                                            balance the tree*/ 
        }
    }

    (root->color) = BLACK;                  /** make root color black*/ 
    return true; 
}
