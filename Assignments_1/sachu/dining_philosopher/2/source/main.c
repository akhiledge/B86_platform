/**
 * File              : main.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \file main.c Main file
 * **/

#include <stdio.h>

int philosopher[SIZE] = {0, 1, 2, 3, 4};        /**< philosopher is an
integer array to store index */
int state[SIZE] = {0};          /**< state is an integer array to store
state of philosopher */

sem_t sem[SIZE];                    /**< semaphore variable */
pthread_mutex_t mutex;              /**< Mutex variable */

int main(void)
{
    int iter;                   /**< iter used for iteration*/
    int status;
    pthread_t tid[SIZE];        /**< Array storing tid*/

    pthread_mutex_init(&mutex, NULL);

    for (iter = 0; iter < SIZE; iter++) {  /* Initialising semaphore */
	sem_init(&sem[iter], 0, 0);
    }

    for (iter = 0; iter < SIZE; iter++) { /* Creating philosopher
	threads */
	status = pthread_create(&tid[iter], NULL,
	philosopher_fun, &philosopher[iter]);
	if (status != 0) {
	    printf("Thread creation failed %s\n", strerror(status));
	}
    }
    pthread_exit(NULL);

    return 0;
}

