/**
 * File              : put_back_spoon.c
 * Author            : Basava Prasad S J
 * Date              : 18.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */

/**@brief :Function To put back the spoons on to the table after eating
 *         completes */

/**header file*/
#include "header.h"

/**global variable declarations*/
extern int phil_arr[NUM_PHIL];   /*Philosopher number*/
/*extern volatile int food_count;  food content for eating*/

/**@brief : put_back_spoon function to keep spoon back on the table after 
 *          eating compltes
 *@param : philosopher number
 *@return : returning nothing*
 */
void put_back_spoon (int phnum)
{
    sem_wait (&sem); 
    *(state_phil + phnum) = WAIT; /*put the philosopher to waiting state*/
    fprintf (stdout, "%d philosopher put back %d and %d\n spoons", 
                            phnum + TRUE, LEFT + TRUE, RIGHT + TRUE);
    fprintf (stdout, "%d philosopher is waiting now\n", phnum + TRUE);

    /**test for the right and left philosophers*/
    test_leftnright (LEFT); 
    test_leftnright (RIGHT);
    sem_post (&sem);             /*unlock for the use of other philosopher*/
}
