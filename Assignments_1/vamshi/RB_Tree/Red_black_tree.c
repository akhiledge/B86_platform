/**
 *
 *  File name           : Red_black_tree.c
 *  Author              : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  File Creation       : 17-07-2018
 *  Created by          : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  Last modification   : 19-07-2018
 *  Last modified by    : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *
 * **/


///// Headers files to be included.
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>   
#include <assert.h>
    
#define Buf_Size 50     //// Buf_size is th max size of the buffer that can be allocate to the buffer

//// childs of the root or parent 
////if 0 its left child(L_child), if 1 its right child(R_child).
#define L_child 0    
#define R_child 1

#define Size 100    //// Size of the stack that is used in insertion function to store the previous nodes.

////colors of the nodes. If R then node color is RED, if B then node color is BLACK.
#define RED 'R'
#define BLACK 'B'

//// structure to built the RB tree.
typedef struct Node{
    int data;               /// integer data member of the node.
    char color;             /// color member to specify the color of the node.
    struct Node *child[2];  /// childs of the node either left or right child.
}RBT;

RBT *root = NULL;           //// root of the tree.

//// post order display for the tree.
void Postorder(RBT *node)
{
    /// checking wheather the root is available or not.
    if( node ){
        //// recursively calling the function to get every node in the tree.
        Postorder( node->child[L_child] );
        Postorder( node->child[R_child] );
        //// printing the node data along with the color.        
        printf( "%d colour:%c\n", node->data, node->color );
    }
    return;
}

//// preorder traversal for the tree.
void Preorder(RBT *node)
{
    /// checking wheather the root is available or not.
    if( node ){
        //// printing the node data along with the color.        
        printf( "%d colour:%c\n", node->data, node->color );
        //// recursively calling the function to get every node in the tree.
        Preorder( node->child[L_child] );
        Preorder( node->child[R_child] );
    }
    return;
}

//// Inorder traversal for the tree.
void Inorder( RBT *node )
{
    /// checking wheather the root is available or not.
    if( node ){
        //// recursively calling the function to get every node in the tree.
        Inorder( node->child[L_child] );
        //// printing the node data along with the color.        
        printf( "%d colour:%c\n", node->data, node->color );
        //// recursively calling the function to get every node in the tree.
        Inorder( node->child[R_child] );
    }
    return;
}

//// creation of the node and inserting the data along with the color.
RBT *CreateNode( int data )
{
    RBT *newnode = NULL;

    newnode = (RBT *)malloc( sizeof( RBT ) );   /// allocating the memory space for the newnode.
    assert(newnode); /// checking wheather the malloc allocated space or not.

    newnode->data = data;   /// Assigning user input value to the node.
    newnode->color = RED;   /// Allocating the color for the node every node color is red while inserting.
    //// for newnode left and right childs are NULL.
    newnode->child[L_child] = NULL; 
    newnode->child[R_child] = NULL;

    return newnode;         //// returning the newly created node.
}

//// Insertion function will insert the node into tree at correct position 
//// with correct color by performing the rotations.
void Insertion( int data )
{
    RBT *temp_node_2 = NULL;
    RBT *temp_node = root;
    RBT *stack[Size];       //// It is used store the traversed nodes
    int child[Size];        //// It is used store which node is moving to which child.
    int index = 0;          //// It is used as index for above stack and child array.
    int value;

    ///// Checking wheather the root is null or not. If null creating the root node.
    if( NULL == root){
        root = CreateNode( data );
        root->color = BLACK;
        return;
    }
    
    stack[index] = root;
    child[index++] = L_child;
    
    //// Find the place to insert the node.
    while( NULL != temp_node ){
        stack[index] = temp_node;

        if( temp_node->data == data ){
            printf("\nDuplicates are not allowed!!!!!!!!\n\n");
            return;
        }

        value = (data - temp_node->data) > 0 ? R_child : L_child;
        temp_node = temp_node->child[value];
        child[index++] = value;
    }
    free(temp_node);
    temp_node = NULL;

    //// create and insert the node.
    stack[index-1]->child[value] = CreateNode( data );
    
    //// checking the index value and the Parent color of the node.
    while( (index >= 3) && (stack[index-1]->color == RED) ){
        if( child[index-2] == L_child ){ //// if the parent is left child of it's then do this.
            temp_node = stack[index-2]->child[R_child];     
            if( (temp_node != NULL) && (temp_node->color == RED) ){ //// change the color of it's parent and uncle to black, if they are red.
                stack[index-2]->color = RED;
                stack[index-1]->color = temp_node->color = BLACK;
                index = index - 2;
            }
            else{
                if( child[index-1] == L_child ){
                    temp_node = stack[index-1];
                }
                else{/////////// Single Left rotation using parent
                    temp_node_2 = stack[index-1];
                    temp_node = temp_node_2->child[R_child];
                    temp_node_2->child[R_child] = temp_node->child[L_child];
                    temp_node->child[L_child] = temp_node_2;
                    stack[index-2]->child[L_child] = temp_node;
                }
                ////// Single Left rotation using grand parent.
                temp_node_2 = stack[index-2];
                temp_node_2->color = RED;
                temp_node->color = BLACK;
                temp_node_2->child[L_child] = temp_node->child[R_child];
                temp_node->child[R_child] = temp_node_2;
                
                if( temp_node_2 == root )
                    root = temp_node;
                else
                    stack[index-3]->child[child[index-3]] = temp_node;
                break;
            }
        }
        else{   //// if the parent is right child of it's parent do this.
            temp_node = stack[index-2]->child[L_child];
            if( (temp_node != NULL) && (temp_node->color == RED) ){///change the color of the parent and uncle to black, if they are red. 
                stack[index-2]->color = RED;
                stack[index-1]->color = temp_node->color = BLACK;
                index = index-2;
            }
            else{
                if( child[index-1] == R_child ){
                    temp_node = stack[index-1];
                }
                else{///////// Single right rotation using parent
                    temp_node_2 = stack[index-1];
                    temp_node = temp_node_2->child[L_child];
                    temp_node_2->child[L_child] = temp_node->child[R_child];
                    temp_node->child[R_child] = temp_node_2;
                    stack[index-2]->child[R_child] = temp_node;
                }
                ////// Single right rotation using grand parent
                temp_node_2 = stack[index-2];
                temp_node->color = BLACK;
                temp_node_2->color = RED;
                temp_node_2->child[R_child] = temp_node->child[L_child];
                temp_node->child[L_child] = temp_node_2;
                
                if( temp_node_2 == root )
                    root = temp_node;
                else
                    stack[index-3]->child[child[index-3]] = temp_node;
                break;
            }
        }
    }

    root->color = BLACK; /////// change the root node color to black.
    return;
}

int main()
{
    int data;
    char *buffer = NULL;
    char choice;

    buffer = (char *)malloc( sizeof(char) * Buf_Size ); //// allocating the memory for buffer.
    assert(buffer); /// checking wheather the memory is allocated or not.

    while( true ){
        printf("\na. Insertion\nb. Inorder\nc. Preorder\nd. Postorder\ne. Exit\n");
        printf("Enter your choice:");  //// take the choice from user.
        __fpurge(stdin);
        choice = getchar();
        
        switch(choice){
            case 'a' :
                printf("Enter the data to insert:");
                __fpurge(stdin);
                data = atoi( fgets(buffer, Buf_Size, stdin) );
                Insertion(data);        //// calling Insertion function.
                break;
            case 'b' :
                printf("\nInorder Traversal:\n");
                Inorder(root);          /// calling Inorder traversal function.
                printf("\n\n");
                break;
            case 'c' :
                printf("\nPreorder Traversal:\n");
                Preorder(root);
                printf("\n\n");         /// calling Preorder traversal function.
                break;
            case 'd' :
                printf("\nPostorder Traversal:\n");
                Postorder(root);        /// calling Postorder traversal function.
                printf("\n\n");
                break;
            case 'e' :
                return 0;
            default :
                printf("\nWrong Choice!!!!!!!\n\n");
                break;          
        }
    }
    
    free(buffer);
    buffer = NULL;

    return 0;
}
