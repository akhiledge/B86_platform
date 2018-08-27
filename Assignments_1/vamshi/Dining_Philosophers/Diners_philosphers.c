/**
 * File              : ../Dining_Philosophers/Diners_philosphers.c
 * Author            : Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 24.08.2018
 * Last Modified By  : Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 5
#define EAT 0
#define HUNGRY 1
#define THINK 2
#define P_MAX 20

/**
 * @Param Philospher[P_MAX] ---> Maximum no.of philosphers that we can take
 *                               P_MAX is macro it can be changed
 * @Param State         ---> It describes Philosopher is in which state
 * @Param Semaphore[MAX]---> Array of individual semaphores for every
 *                           philosopher MAX is macro it is the no.of
 *                           philosophers
 * @Param Mutex         ---> Common semaphore for all the philosophers
 */
int Philospher[P_MAX] = {0, 1, 2, 3, 4,
			 5, 6, 7, 8, 9,
			 10, 11, 12, 13, 14,
			 15, 16, 17, 18, 19};
int State[MAX];
sem_t Semaphore[MAX];
sem_t Mutex;

/**
 * @Synopsis  --->  Check function will checks weather the philosopher is
 *                  in think state or not. If philosopher is in think
 *                  state and checks the forks are available or not.
 *                  change philosopher state to eat state and after some
 *                  time put forks down.
 *
 * @Param Philospher_num ---> To know weather which philosopher is
 *                            going to eat state.
 */
void
Check(int Philospher_num)
{
    int left = (Philospher_num + (MAX-1)) % MAX;
    int right = (Philospher_num + 1) % MAX;

    if (State[Philospher_num] == HUNGRY
	    && State[left] != EAT && State[right] != EAT){
	State[Philospher_num] = EAT;
	sleep(2);
	printf("Philospher %d is taking forks %d and %d\n",
		Philospher_num + 1, left+1, Philospher_num + 1);
	printf("Philospher %d is Eating\n", Philospher_num + 1);
	sem_post(&Semaphore[Philospher_num]);
    }
    return;
} /** End of check function*/

/**
 * @Synopsis  --->  lock the common semaphore and change philosopher
 *                  state to hungry and callng the check function
 *                  after that releasing common semaphore.
 *
 * @Param Philospher_num  ---> to know the which philosopher is in
 *                             hungry state.
 */
void
Taking_fork(int Philospher_num)
{
    sem_wait(&Mutex);
    printf("Philospher %d is hungry\n", Philospher_num + 1);
    State[Philospher_num] = HUNGRY;
    Check(Philospher_num);
    sem_post(&Mutex);
    sem_wait(&Semaphore[Philospher_num]);
    sleep(1);
    return;
} /** End of Taking_fork function*/

/**
 * @Synopsis   ---> this function will change the philosopher state
 *                  to thinking and put down the forks after that it
 *                  is calling the check function to check availability
 *                  of forks.
 *
 * @Param Philospher_num  --->  to know which philosopher is putting
 *                              down the forks.
 */
void
Puting_fork(int Philospher_num)
{
    int left = (Philospher_num + (MAX-1)) % MAX;
    int right = (Philospher_num + 1) % MAX;

    sem_wait(&Mutex);
    State[Philospher_num] = THINK;
    printf("Philospher %d is putiing forks %d and %d down\n",
	    Philospher_num + 1, left + 1, Philospher_num + 1);
    printf("Philospher %d is thinking\n", Philospher_num + 1);
    Check(left);
    Check(right);
    sem_post(&Mutex);
    return;
} /** End of Putting_fork fuinction */

/**
 * @Synopsis  --->  This function is creating philosophers and putting
 *                  state as thinking state.
 *
 * @Param num ---> num is the identification number of the philosopher.
 *
 * @Returns   ---> this function is returning NULL to the calling
 *                 function.
 */
static void
*Philosphers(void *num)
{
    int *index = num;

    State[*index] = THINK;
    sleep(2);
    Taking_fork(*index);
    sleep(1);
    Puting_fork(*index);
    return NULL;
} /** End of Philosphers function */

/**
 * @Synopsis  --->  Main function for the Dining philosophers. It is
 *                  creating philosophers and semaphores for each
 *                  philosopher.
 *
 * @Returns   --->  main is returning 0 to startup function.
 */
int main(void)
{
    int index;
    pthread_t Thread[MAX];

    sem_init(&Mutex, 0, 1);
    for (index = 0; index < MAX; index++) {
	sem_init(&Semaphore[index], 0, 1);
    }
    for (index = MAX - 1; index >= 0; index--) {
	pthread_create(&Thread[MAX], NULL, &Philosphers,
					&Philospher[index]);
	printf("Philospher %d is Thinking\n", index+1);
    }
    pthread_exit(NULL);
    return 0;
} /** End of main */
