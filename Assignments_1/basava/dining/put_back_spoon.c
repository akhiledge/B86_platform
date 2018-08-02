/**Function To put back the spoons */

///header file
#include "header.h"

///global variable declarations
extern int phil_arr[NUM_PHIL];
extern volatile int food_count;

/**function definition */
void put_back_spoon (int phnum)
{
    sem_wait (&sem); //lock untill philosopher put back the spoons

    *(state_phil + phnum) = WAIT; //put the philosopher to waiting state
    fprintf (stdout, "%d philosopher put back %d and %d\n spoons", phnum + TRUE,
                            LEFT + TRUE, RIGHT + TRUE);
    fprintf (stdout, "%d philosopher is waiting now\n", phnum + TRUE);

    /*test for the right and left philosophers*/
    test_leftnright (LEFT); 
    test_leftnright (RIGHT);

    sem_post (&sem); //unlock for the use of other philosopher
}
