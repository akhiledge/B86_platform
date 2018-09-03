
/**
 * File              : app_dining_sem.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 18.07.2018
 * Brief			 : Dining philosopher solution using
					   mutex and semaphore
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**inclusion of header file*/
#include "header.h"

/** Global variables defined ..*/
int philosophers[NUM] = {0, 1, 2, 3, 4}; /**Number of philosophers*/
int right;
int left;

/**@brief: Function to invoke take_fork and place_fork
 * @param: phil_num of type int
 * @return: returns void
 */
void *philosopher_fn(void *phil_index)
{
	int *phil_addr = NULL;
	phil_addr = (int *) phil_index;
	printf("Philosopher %d is THINKING\n", *phil_addr + 1);
	while (1) {
		sleep(2);
		take_fork(*phil_addr); /**function call to pick the fork*/
		sleep(2);
		place_fork(*phil_addr); /**function call to place the fork again*/
	}
}

/**@brief: Function definition to pick the forks
 * @param: Phil_num of type int
 * @return: returns void
 */
void take_fork(int phil_num)
{
	sem_wait(&sem_main);
	state[phil_num] = HUNGRY; /**state of philosopher is hungry*/
	printf("Philosopher %d is HUNGRY\n", phil_num + 1);
	check_avail_fork(phil_num); /**has to check availability of left and
								  right forks*/
	sem_post(&sem_main);
	sem_wait(&sem[phil_num]);
}

/**@brief: Function to check availability of left and right forks
 * @param: phil_num of type int
 * @return: returns void
 */
void check_avail_fork(int phil_num)
{
	right = (phil_num == 0) ? NUM-1 : phil_num - 1;
	left = (phil_num == NUM-1) ? 0 : phil_num + 1;
	if ((state[phil_num] == HUNGRY) && (state[left] != EATING) 
		&& (state[right] != EATING)) { /**check state of philosopher is
										 hungry,left and right forks are
										 available*/
		state[phil_num] = EATING;
		printf("Forks taken %d and %d by philosopher %d\n",
						right+1, phil_num+1, phil_num + 1);
		printf("Philosopher %d is EATING\n", phil_num + 1);
		sleep(1);
		sem_post(&sem[phil_num]);
	}
}

/**@brief: Function definition to place the forks back
 * @param: phil_num of type int
 * @return: returns void
*/
void place_fork(int phil_num)
{
	sem_wait(&sem_main);
	right = (phil_num == 0) ? NUM-1 : phil_num - 1;
	left = (phil_num == NUM-1) ? 0 : phil_num+1;

	state[phil_num] = THINKING;

	printf("Forks %d and %d are placed again by philosopher %d\n",
								right+1, phil_num+1, phil_num+1);
	printf("Philosopher %d is again THINKING\n", phil_num+1);

	check_avail_fork(left); /**has to check availability of forks for
							  left philosopher*/
	check_avail_fork(right);/**has to check availability of forks for
							  right philosopher*/
	sem_post(&sem_main);
}

/**@brief: Creates threads depending on number of philosophers
 * @param: No arguments
 * @return: returns 0 on success
 */
int main(void)
{
	pthread_t th_id[NUM];
	int status = 0;
	int index = 0;

	sem_init(&sem_main, 0, 1);
	for (index = 0; index < NUM; index++) {
		sem_init(&sem[index], 0, 0);
	}

	for (index = 0; index < NUM; index++) {
		status = pthread_create(&th_id[index], NULL, philosopher_fn,
				&philosophers[index]); /**creation of threads*/
		if (status != 0) { /**Validation of pthread_create*/
			perror("Pthread:%s\n");
		}
	}
	pthread_exit(NULL);
	return 0;
}
