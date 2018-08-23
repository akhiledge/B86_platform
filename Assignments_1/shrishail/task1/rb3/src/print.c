/**
 * File:print.c
 * Description:Printing the nodes
 * Date:23-8-18
 * Last modified:23-8-18
 */

void print(rbtree *root) {                                                     
    inorder(root); ///function call for inorder traversal   
}                                                                               

///Inorder function(Recursive)                                                  
void inorder(rbtree *root)                                                     
{                                                                               
    if (root != NULL) {
        inorder(root->left);                                                    
        printf("%d\t", root -> val);                                           
        if (root->color) {
            printf("RED\n");
        }
        else {
            printf("BLACK\n");
        }                        
        inorder(root -> right);                                                 
    }                                                                           
}                    
