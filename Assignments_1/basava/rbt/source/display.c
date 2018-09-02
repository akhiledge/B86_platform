/**
 * File              : display.c
 * Author            : Basava Prasad S J
 * Date              : 20.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */
/** @brief : Display function for Different traversal methods like :
            *pre-order traversal
            *post-order traversal
            *in-order traversal
*/

/**header file inlcusion*/
#include "rbt_header.h"

/**@param : Root node of the RB tree
 * @return : No return values
 */

void display_nodes (RBT_NODE *root)
{                                                            
    /**variables declarations*/
     int choice = 0;                  /*to select traversal method */
     char *str = NULL;

     str = (char *) malloc (sizeof (int));
     assert (str);                    /*NULL condition validation */

     /**different traversal methods selection*/                                       
     fprintf (stdout, "Enter the choice to traverse:\
                                     \n\r1.Pre_order\
                                    \n\r2.Post_order\
                                    \n\r3.In_order\n");
     choice = my_atoi (fgets (str, sizeof (int), stdin));
     assert (str);

     switch (choice) {  
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
/**@brief :  pre-order traversal function to display in NLR manner
 * @param : Root of the RB tree
 * @return : returning no values
*/
void preorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL) {  
        fprintf (stdout, "Node is : %d and color is : %d\n", 
                               root -> data, root -> color);
        preorder_traversal (root -> lchild);
        preorder_traversal (root -> rchild);
    }
}
/**@brief : post-order traversal function to display in LRN manner
 * @param : Root of the RB tree
 * @return : returning no values
*/
void postorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL) {  
        postorder_traversal (root -> lchild);
        postorder_traversal (root -> rchild);
        fprintf (stdout, "Node is : %d and color is : %d\n", 
                               root -> data, root -> color);
    }
}
/**@brief : in-order traversal function to display in LNR manner
 * @param : Root of the RB tree
 * @return : returning no values
*/
void inorder_traversal (RBT_NODE *root)
{                                                            
    if (root != NULL) {  
        inorder_traversal (root -> lchild);
        fprintf (stdout, "Node is : %d and color is : %d\n", 
                               root -> data, root -> color);
        inorder_traversal (root -> rchild);
    }
}

