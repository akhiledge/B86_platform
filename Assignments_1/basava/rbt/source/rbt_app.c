/**
 * File              : rbt_app.c
 * Author            : Basava Prasad S J
 * Date              : 20.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */
/** @brief : Application to Imlement a RB tree Insertion and display */

/**Header file inclusion */
#include "rbt_header.h"

/**@brief : main function to provide user interface for RB tree implentation
 *          and to call Insertion and display functions.
 *@param : No parameters
 *@return : Returning a integer value zero on success
 */

int main (void) 
{
    /**variable declarations*/
    int select = 0;                                  /*user choice of 
                                                       operation*/
    int element = 0;                                 /*data to insert */
    char *str = NULL;
    RBT_NODE *root = NULL;

    str = (char *) malloc (sizeof (char) * STR_SIZE); /*dynamic memory 
                                                        allocation for str*/
    assert (str);                                     /*validating for 
                                                        NULL condition */

    for (; ;) {
        fprintf (stdout, "Enter the choice :\
                            \n\r1.Insertion \
                            \n\r2.Deletion \
                            \n\r3.Display\n");        /*user choice for 
                                                        operation*/
        select = my_atoi (fgets (str, sizeof (int), stdin));
        assert (str);                                 /*validating NULL 
                                                        condition*/

        switch (select) {                             /*user choice operation*/
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
