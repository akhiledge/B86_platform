
/**
 * File              : fork_release.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
extern int state[SIZE];
extern pthread_mutex_t mutex;
/*
 * \brief Function definition for releasing fork
 * \param value is philosopher index
 * */
void fork_release(int value)
{
    pthread_mutex_lock(&mutex);       /* Mutex locking */

    state[value] = THINKING;         /* State change */
    printf("Philosopher %d released forks %d and %d\n", (value + 1),
    LEFT_P  + 1, value + 1);

    check_for_fork(LEFT_P);             /* Function call to check for
					   blocked left philosopher */
    check_for_fork(RIGHT_P);            /* Function call to check blocked
					   right philosopher */

    pthread_mutex_unlock(&mutex);       /* Mutex unlock */
}
