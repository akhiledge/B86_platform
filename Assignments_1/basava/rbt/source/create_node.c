/** creating a node of type RBT_NODE */

///Header file
#include "rbt_header.h"

/**creating node function definition */

RBT_NODE *create_node ()
{
    ///variable declarations
    RBT_NODE *newnode = NULL; //to create a new node
    int element = 0;          //to hold the data
    char *str = NULL;

    str = (char *) malloc (sizeof (char) * STR_SIZE); //to store element
    assert (str);   //validating NULL condition

    newnode = (RBT_NODE *) malloc (sizeof (RBT_NODE)); //allocating memory
    assert (newnode);  //validating NULL condition

    fprintf (stdout, "Enter the element insert\n");
    __fpurge (stdin);
    element = my_atoi (fgets (str, sizeof (int), stdin));
    assert (str);  //validating NULL condition

    newnode -> data = element;     //to store the data element
    newnode -> color = Red;        //color of the node
    newnode -> rchild = NULL;      //right child address
    newnode -> lchild = NULL;      //left child address
    newnode -> parent = NULL;

    return newnode;          //returnig a created node
}
