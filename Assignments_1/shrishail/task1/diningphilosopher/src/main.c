
/*
 * File:main.c
 * author:shrishail satihal
 * Description:dining philosopher problem
 * date:13-7-18
 * Last modified:23-8-18
 * Last modified by:Shrishail Satihal <s.shrishail@globaledgesoft.com>
 */

int philospher1[SIZE] = { 0, 1, 2, 3, 4 };
int main(void)
{
    int index;

    pthread_t thread_id[SIZE];
    sem_init(&sem, 0, 1); /*initialize the semaphores*/
    for (index = 0; index < SIZE; index++)
     sem_init(&Semaphore[index], 0, 0);
    for (index = 0; index < SIZE; index++) {
    /*create philosopher threads*/
    pthread_create(&thread_id[index], NULL, philosopher,\
    &philospher1[index]);
    printf("Philosopher %d is thinking\n", index + 1);
    }
    for (index = 0; index < SIZE; index++)/*wait till the complete
    execution of particular philosopher using pthread_join*/
     pthread_join(thread_id[index], NULL);
    pthread_exit(NULL);
    return 0;
}
