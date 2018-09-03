/**
 * File              : test_leftnright.c
 * Author            : Basava Prasad S J
 * Date              : 18.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */

/**header file inclusion*/
#include "header.h"

/**Global variable declarations */
extern int phil_arr[NUM_PHIL];                 /** philosopher number */
/*extern volatile int food_count;               **food content to eat */

/** @brief : Checking for the state of neighbour philosophers 
 * @param : Philosopher number
 * @return : returning nothing
 */
void test_leftnright (int phnum)
{
    if (*(state_phil + phnum) == DESPARATE && *(state_phil + LEFT) != EAT 
            && *(state_phil + RIGHT) != EAT){  /*condition to cheack right 
                                                 and left philosophers state*/
       *(state_phil + phnum) = EAT;            /*make the philosopher eat*/
       /*--(food_count);*/

        sleep (TRUE);
        fprintf (stdout, "%d philosopher takes the spoon %d and %d\n", 
                             phnum + TRUE, RIGHT + TRUE, LEFT + TRUE);
        fprintf (stdout, "%d philosopher eating\n", phnum + TRUE);

        sem_post (&sem_val[phnum]);             /*to indicate the eating 
                                                  philosopher*/
    }
}
