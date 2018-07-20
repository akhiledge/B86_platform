/** Checking for the state of neighbou philosophers */

///header file
#include "header.h"

/**Global variable declarations */
extern int phil_arr[NUM_PHIL];
extern volatile int food_count;

/**function definition */
void test_leftnright (int phnum)
{
    if (*(state_phil + phnum) == DESPARATE && *(state_phil + LEFT) != EAT &&
            *(state_phil + RIGHT) != EAT){  /*condition to cheack right and left
                                        philosophers state*/
       *(state_phil + phnum) = EAT;     //make the philosopher eat
       --(food_count);

        sleep (TRUE);
        fprintf (stdout, "%d philosopher takes the spoon %d and %d\n", phnum +
                                TRUE, RIGHT + TRUE, LEFT + TRUE);
        fprintf (stdout, "%d philosopher eating\n", phnum + TRUE);

        sem_post (&sem_val[phnum]);  //to indicate the eating philosopher
    }
}
