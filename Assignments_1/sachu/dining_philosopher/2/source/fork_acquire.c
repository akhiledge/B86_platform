
/**
 * File              : fork_acquire.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

extern int state[SIZE];         /**< extern variable state */
extern sem_t sem[SIZE];         /**< extern variable semaphore */
extern pthread_mutex_t mutex;   /**< extern variable mutex */

/*
 * \brief Function definition to acquire fork
 * \param value is the philosopher index
 * */
void fork_acquire(int value)
{
    pthread_mutex_lock(&mutex);     /* Locking mutex */
    state[value] = HUNGRY;          /* State change */
    printf("philosopher %d is hungry\n", (value + 1));
    check_for_fork(value);          /* Function call for checking
				       fork availability */
    pthread_mutex_unlock(&mutex);   /* Unlocking mutex */
    sem_wait(&sem[value]);     /* Semaphore wait for confirming
				  fork acquire */
    sleep(1);
}
