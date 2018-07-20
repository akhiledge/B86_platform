/** Application to Imlement a RB tree */

///Header file
#include "rbt_header.h"

/**main function definition*/

int main (void) 
{
    ///variable declarations
    int select = 0;
    int element = 0;
    char *str = NULL;
    RBT_NODE *root = NULL;

    str = (char *) malloc (sizeof (char) * STR_SIZE); /*dynamic memory allocati
                                                     -on for str*/
    assert (str);               //validating for NULL condition

    for (; ;){
        fprintf (stdout, "Enter the choice :\
                        \n\r1.Insertion \
                        \n\r2.Deletion \
                        \n\r3.Display\n");  //user choice for operation
        select = my_atoi (fgets (str, sizeof (int), stdin));
        assert (str);      //validating NULL condition

        switch (select){    //user choice operation
            case Insertion :
                root = insert_node (root);
                break;

          /*  case Deletion :
                root = delete_node (root);
                break;*/

            case Display :
                display_nodes (root);
                break;

            default : 
                fprintf (stdout, "wrong choice of operation\n");
                      break;
        }
    }

    return 0;
}
