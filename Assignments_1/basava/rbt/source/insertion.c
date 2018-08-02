/** Insertion of node to the RB_tree */

///Header file
#include "rbt_header.h"

/**insertion function definition */

RBT_NODE *insert_node (RBT_NODE *root)
{
    ///variable declarations
    RBT_NODE *newnode = NULL;
    RBT_NODE *temp_ptr_current = NULL; //temporary pointers
    RBT_NODE *temp_ptr_parent = NULL;

    newnode = create_node (); //create a node to insert to the tree
    assert (newnode);   //validating NULL condition
    
    //memory allocation and validations for temporary pointers
    temp_ptr_current = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp_ptr_current);

    temp_ptr_parent = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp_ptr_parent);

    //No node condition
    if (root == NULL){    //if there is no nodes make newnode as root node
        root = newnode;
        root -> color = Black;
        return root;
    }
    else{                   //if tree is present insertion accordingly
        temp_ptr_current = root;
        while (SUCCESS){     //untill the insertion is successfull

            temp_ptr_parent = temp_ptr_current;
            if (temp_ptr_parent -> data < newnode -> data){  //to the right-side
                temp_ptr_current = temp_ptr_parent -> rchild;

                if (temp_ptr_current == NULL){
                    temp_ptr_parent -> rchild = newnode;
                    newnode -> parent = temp_ptr_parent;
                //    printf ("hi\n");
                    break;

                }
            }
            else if(temp_ptr_parent -> data > newnode -> data){ //to left side
                temp_ptr_current = temp_ptr_parent -> lchild;
                    
                if (temp_ptr_current == NULL){ 
                    temp_ptr_parent -> lchild = newnode;
                    newnode -> parent = temp_ptr_parent;
                    printf ("hi\n");
                    break;
                }                                   
            }
            else{                             //if the element is duplicate
                fprintf (stdout, "Duplicate elements are not allowed\n");
                return;              
            }          
         }
        root = insert_color (newnode, root);
     }
    return root;
}

/**insertion of node according to color balancing*/
///insertion according to color function definition

RBT_NODE *insert_color (RBT_NODE *newnode, RBT_NODE *root)
{                                                            
    RBT_NODE *grand_parent = NULL; //temporary pointer
    RBT_NODE *uncle = NULL;

    grand_parent = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (grand_parent);

    uncle = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (uncle);

    if (newnode -> parent -> parent != NULL){

        if (newnode -> parent -> parent -> lchild == newnode -> parent){
            uncle = newnode -> parent -> parent -> rchild;
        }
        else{
            uncle = newnode -> parent -> parent -> lchild;
        }
    
    grand_parent = newnode -> parent -> parent;
    
    /*to check whether parent and uncle is red color or not*/

    if ((newnode -> parent != NULL) && (newnode -> parent -> color == Red)){
        if (grand_parent -> lchild != newnode -> parent){

            if ((grand_parent -> lchild -> color == Red) && 
                (grand_parent -> lchild != NULL)){

                grand_parent -> lchild -> color = Black;
                grand_parent -> color = Red;
                newnode -> parent -> color = Black;
                newnode = grand_parent;
            }

            else{
                grand_parent -> rchild -> color = Black;
                grand_parent -> color = Red;
                newnode -> parent -> color = Black;
                newnode = grand_parent;
            }
            if ((newnode -> parent == NULL) && (newnode -> color == Red)){
                newnode -> color = Black;
                root = newnode;
                return root;
            }
        }
    }
    /*if uncle is black we can have following conditions */
    if ((uncle == NULL) || (uncle -> color = Black)){
        /*left-left case*/
        if ((newnode -> parent -> lchild == newnode) && (grand_parent -> lchild
                                                == newnode -> parent)){
            root = rotate_right (grand_parent, root);
            return root;
        }
        /*left-right case*/
        else if ((newnode -> parent -> rchild == newnode) && (grand_parent -> 
                                        lchild == newnode -> parent)){
            root = rotate_right_left (grand_parent -> rchild, root);
            root = rotate_left (grand_parent, root);
            return root;
        }
        /*right-right case*/
        else if ((newnode -> parent -> rchild == newnode) && (grand_parent 
                                          -> rchild == newnode -> parent)){
            root = rotate_left (grand_parent, root);
            return root;
        }
        /*right-left case*/
        else if ((newnode -> parent -> lchild == newnode) && (grand_parent -> 
                                        rchild == newnode -> parent)){
            root = rotate_left_right (grand_parent -> lchild, root);
            root = rotate_right (grand_parent, root);
            return root;
        }
    }
    }
    return root;
}

/**function definition for right rotation of child, parent and grandparent 
 * nodes */
RBT_NODE *rotate_right (RBT_NODE *grandparent, RBT_NODE *root)
{
    RBT_NODE *temp = NULL; //temporary pointer to parent
    int color_swap = grandparent -> color;

    temp = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp);
    temp = grandparent -> lchild;
    
    if (grandparent -> parent == NULL){  /*to do right rotate if grandparent is
                                            root*/
        grandparent -> parent = temp;
        temp -> rchild = grandparent;
        temp -> parent = NULL;
        grandparent -> lchild = NULL;
    /*after rotation swap the color of parent and grandparent*/

        grandparent -> color = temp -> color;
        temp -> color = color_swap;
        root = temp;
    }
    else{ /*if grandparent is not root */
        
        temp -> parent = grandparent -> parent;
        temp -> rchild = grandparent;
        grandparent -> parent -> lchild = temp;
        grandparent -> parent = temp;
        grandparent -> lchild = NULL;

        /* swap the colors of parent and grandparent */
        grandparent -> color = temp -> color;
        temp -> color = color_swap;
    }
    return root;
}
/**function definition for left rotation of child, parent and grandparent 
 * nodes */
        
RBT_NODE *rotate_left (RBT_NODE *grandparent, RBT_NODE *root)
{
    RBT_NODE *temp = NULL; //temporary pointer to parent
    int color_swap = grandparent -> color;

    temp = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp);
    temp = grandparent -> rchild;
    
    if (grandparent -> parent == NULL){  /*to do right rotate if grandparent is
                                            root*/
        grandparent -> parent = temp;
        temp -> lchild = grandparent;
        temp -> parent = NULL;
        grandparent -> rchild = NULL;
    /*after rotation swap the color of parent and grandparent*/

        grandparent -> color = temp -> color;
        temp -> color = color_swap;
        root = temp;
    }
    else{ /*if grandparent is not root */
        
        temp -> parent = grandparent -> parent;
        temp -> lchild = grandparent;
        grandparent -> parent -> rchild = temp;
        grandparent -> parent = temp;
        grandparent -> rchild = NULL;

        /* swap the colors of parent and grandparent */
        grandparent -> color = temp -> color;
        temp -> color = color_swap;
    }
    return root;
}
/*function definition for left-right case*/
RBT_NODE *rotate_left_right (RBT_NODE *parent_new, RBT_NODE *root)
{
    RBT_NODE *temp = NULL;//temporary pointer
    temp = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp);

    temp = parent_new -> rchild;
    /*rotate right to get left-left case*/
    temp -> parent = parent_new -> parent;
    parent_new -> parent -> lchild = temp;
    parent_new -> parent = temp;
    temp -> lchild = parent_new;
    
    return root;
}
/*function definition for right-left case*/
RBT_NODE *rotate_right_left (RBT_NODE *parent_new, RBT_NODE *root)
{
    RBT_NODE *temp = NULL;//temporary pointer

    temp = (RBT_NODE *) malloc (sizeof (RBT_NODE));
    assert (temp);
    temp = parent_new -> lchild;
    /*rotate right to get right-right case*/
    temp -> parent = parent_new -> parent;
    parent_new -> parent -> rchild = temp;
    parent_new -> parent = temp;
    temp -> rchild = parent_new;
    
    return root;
}


        








      
