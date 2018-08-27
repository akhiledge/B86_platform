
/*
 *File:main.c
 *Author:shrishail satihal
 *Description:Dining philosopher problem
 *Date:23-8-18
 *Last modified:23-8-18
 */

int philospher1[SIZE] = {0, 1, 2, 3, 4}; /*!@ phil is an array of SIZE*/
int main(void)
{
    int index; /*!@index index is integer variable*/

    pthread_t thread_id[SIZE];
    sem_init(&sem, 0, 1);
    for (index = 0; index < SIZE; index++)
        ///semaphore initialization for all 10 processes
        sem_init(&Semaphore[index], 0, 0);
    for (index = 0; index < SIZE; index++) {
        ///create thread for each philosopher
        pthread_create(&thread_id[index], NULL, philosopher,\
                &philospher1[index]);
        printf("philosopher %d is thinking\n", index + 1);
    }
    ///wait till the complete execution of particular \
    philosopher using pthread_join
        for (index = 0; index < SIZE; index++)
            pthread_join(thread_id[index], NULL);
    pthread_exit(NULL);
    return 0;
}

