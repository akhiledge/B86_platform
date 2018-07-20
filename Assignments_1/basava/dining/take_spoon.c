/**Function to collect the spoon for the philosopher*/

///header file
#include "header.h"

/**global variable declarations */

extern int phil_arr[NUM_PHIL];
extern volatile int food_count;

/** function definition */
void take_the_spoon (int phnum)
{
    sem_wait (&sem);  //to lock untill philosopher taking the spoon and eat
    
    *(state_phil + phnum) = DESPARATE;
    test_leftnright (phnum); //to check the availability of spoon

    sem_post (&sem); //other philosopher can ocuupy the spoon now
    sem_wait (&sem_val[phnum]); //to indicate eating is done

    sleep (TRUE);  //next philosopher can eat now
}
    
