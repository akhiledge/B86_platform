
/**
 * File              : philosopher.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/*
 * \brief Dining philosopher problem solution
 * Each philosopher can access forks given by binary semaphores
 *and proceed eating
 **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 5					/**< Size of buffer */

#define LEFT ((*temp + (SIZE - 1)) \
	% SIZE)                 /**< Fork selection */

int     philosopher[SIZE] = { 0, 1, 2, 3, 4 }; /**< Philosopher  array */

sem_t   sem[SIZE];				/**< Semaphore array */

/*
 * \brief Function definition eat
 * \param temp is philosopher index
 * */
void
eat(int *temp)
{
	printf("philosoher %d eating with fork %d and %d\n", (*temp + 1),
			(*temp + 1), (LEFT + 1));
	sleep(1);
}

/*
 * \brief Philosopher Function definition
 * \brief Acquires fork by calling semaphore wait
 * \brief Releases fork by semaphore post
 * \param value is void pointer storing address of philosopher index
 * */

void   *
philosopher_loop(void *value)
{

	int    *temp = value;			   /**< Philosopher index */

	while (1) {
		printf("philosoher %d is hungry\n", (*temp + 1));
		sem_wait(&sem[*temp]);	/* Corresponding fork acquisition */
		sem_wait(&sem[(*temp + 1) 
			% SIZE]);           /* Next fork aquisition */
		printf("philosoher %d taken fork %d and %d\n", (*temp + 1),
				(*temp + 1), (LEFT + 1));
		eat(temp);				/* Function call for eat */
		printf("philosoher %d leaving fork %d and %d\n", (*temp + 1),
				(*temp + 1), (LEFT + 1));
		sem_post(&sem[*temp]);	/* Release of corresponding fork */
		sem_post(&sem[((*temp + 1)
								% SIZE)]);	/*Release of next fork */
		sleep(2);				/* Invoking other
								   hungry philosophers */
	}
}

/*
 * \brief Creating philosopher threads and initialising
 * semaphores for forks
 * */
int
main(void)
{

	int     iter = 0;			/**< Loop variable */
	int     ret = 0;

	pthread_t tid[SIZE];		/**< Thread ID */

	for (iter = 0; iter < SIZE; iter++) {
		sem_init(&sem[iter], 0, 1);
	}
	for (iter = 0; iter < SIZE; iter++) {	/* Creation of
											   philosopher threads */
		ret = pthread_create(&tid[iter],
				NULL, philosopher_loop, &philosopher[iter]);
		assert(!ret);
	}
	pthread_exit(NULL);
}
