/** Display function for Different traversal methods */

///header file inlcusion
#include "rbt_header.h"

/**display function definition */

void display_nodes (RBT_NODE *root)
{                                                            
    ///variables declarations
     int choice = 0;
     char *str = NULL;

     str = (char *) malloc (sizeof (int));
     assert (str);

     ///different traversal methods selection                                       
     fprintf (stdout, "Enter the choice to traverse:\
                           \n\r1.Pre_order\
                           \n\r2.Post_order\
                           \n\r3.In_order\n");
     choice = my_atoi (fgets (str, sizeof (int), stdin));
     assert (str);

     switch (choice){  
           case Pre_order :
                fprintf (stdout, "Pre-order Traversal is :\n");
                preorder_traversal (root);
                break;

           case Post_order :
                fprintf (stdout, "Post-order Traversal is :\n");
                postorder_traversal (root);
                break;

           case In_order :
                fprintf (stdout, "In-order Traversal is :\n");
                inorder_traversal (root);
                break;

           default : fprintf (stdout, "Wrong choice entered\n");
                     break;
     }
}
/** pre-order traversal function definition */
void preorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL){  
        fprintf (stdout, "Node is : %d and color is : %d\n", root -> data,\
                                                           root -> color);
        preorder_traversal (root -> lchild);
        preorder_traversal (root -> rchild);
    }
}
/** post-order traversal function definition */
void postorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL){  
        postorder_traversal (root -> lchild);
        postorder_traversal (root -> rchild);
        fprintf (stdout, "Node is : %d and color is : %d\n", root -> data,\
                                                           root -> color);
    }
}
/** in-order traversal function definition */
void inorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL){  
        inorder_traversal (root -> lchild);
        fprintf (stdout, "Node is : %d and color is : %d\n", root -> data,\
                                                           root -> color);
        inorder_traversal (root -> rchild);
    }
}

