/**
 * File              : app.c
 * Author            : Basava Prasad S J 
 * Date              : 18.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */

/** @brief : Application to solve Dining Philosopher problem 
 * using semaphores */

/**header file inclusion */
#include "header.h"

int phil_arr[NUM_PHIL] = { 0, 1, 2, 3, 4 };/*Number of philosophers */

/*volatile int food_count = FOOD_COUNT;    Food content for each philosopher*/

/**@brief : philosopher thread definition to determine state of philosopher
 * @param : Index to determine the philosopher
 * @return : returning void to the main function
 */

void *philosopher(void *index)
{
	/**since there are 5 philosophers all has to be synchronized to eat*/

	while (TRUE) {				           /*continuos till everyone 
                                             completes eating*/
		int    *phnum = NULL;	           /**@var : variable declarations */
		phnum = (int *)index;

		sleep(TRUE);
		take_the_spoon(*phnum);	           /*to collect both the spoons */
		sleep(FALSE);
		put_back_spoon(*phnum);	           /*after eating put the spoons 
                                             back on table */
	/*	if (food_count == FALSE) {
			exit(0);
		} */
	}
}

/**@brief : main function to create the threads for each philosopher and
            printing the status of each philosopher.
*@param : no parameters
*@return :returning a success condition as zero
*/

int main(void)
{
	/**@var : variables Initializations*/

	sem_init(&sem, THREAD, INIT_VAL_SEM); /*initialise the locking semaphore*/
	int     index = INIT_VAL; 
	int     status = INIT_VAL;
	pthread_t th[NUM_PHIL];		          /*thread for each philosopher*/

    /**semaphore for each philosopher initialised to zero*/
	while (index < NUM_PHIL) {
		sem_init(&sem_val[index], THREAD, INIT_VAL);
		index++;
	}

    /**creating threads for each philosophers*/
	for (index = INIT_VAL; index < NUM_PHIL; index++) {                                                         
		status = pthread_create(&th[index], NULL, philosopher,
				                &phil_arr[index]);
		if (status < FALSE) {
			fprintf(stdout, "%d\n thread creation failed\n", index);
		}
		fprintf(stdout, "%d philosopher is waiting\n", index + TRUE);
	}
	index = INIT_VAL;
    /**main thread waiting for all sub threads */
	while (index < NUM_PHIL) {	
		pthread_join(th[index], NULL);
		index++;
	}
	return INIT_VAL;
}
