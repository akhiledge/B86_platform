/**
 * File              : take_spoon.c
 * Author            : Basava Prasad S J
 * Date              : 18.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */

/*header file includion */
#include "header.h"

/**global variable declarations */

extern int phil_arr[NUM_PHIL];  /*philosopher number */
/*extern volatile int food_count;  food content to eat */

/**@brief : Function to collect the spoon for the philosopher
 * @param: Philosopher number
 * @return : returning nothing
 */

void take_the_spoon (int phnum)
{
    sem_wait (&sem);            /*to lock untill philosopher taking the spoon 
                                  and eat*/
    *(state_phil + phnum) = DESPARATE;
    test_leftnright (phnum);    /*to check the availability of spoon*/
    sem_post (&sem);            /*other philosopher can ocuupy the spoon now*/
    sem_wait (&sem_val[phnum]); /*to indicate eating is done*/
    sleep (TRUE);               /*next philosopher can eat now*/
}
    
