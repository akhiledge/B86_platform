/*
 * @author Sachu George
 * @date 15/07/2018
 * @brief Dining philosopher problem solution
 **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
/*
 * @Macro definitions for SIZE and LEFT
 * */
#define SIZE 5
#define LEFT (*temp + (SIZE - 1)) % SIZE

int philosopher[SIZE] = {0, 1, 2, 3, 4}; /*! Philosopher integer array*/
sem_t sem[SIZE];               /*!Semaphore array*/

/*
 * @brief Function definition eat
 * @param value is philosopher index
 * */
void eat(int *temp)
{
    printf("philosoher %d eating with fork %d and %d\n", (*temp + 1), (*temp + 1), (LEFT + 1));
    sleep(1);
}

/*
 * @brief Philosopher Function definition
 * @param value is void pointer storing address of philosopher index
 * @brief Acquires fork by calling semaphore wait
 * @brief Releases fork by semaphore post
 * */
void *philosopher_loop(void *value)
{
    int *temp = value;
    while(1)
    {

        printf("philosoher %d is hungry\n",(*temp + 1));

        sem_wait(&sem[ *temp ]);             ///Corresponding fork acquisition
        sem_wait(&sem[ (*temp + 1) % SIZE]); ///Next fork aquisition

        printf("philosoher %d taken fork %d and %d\n",( *temp + 1), (*temp + 1), (LEFT + 1));
        eat(temp);                           ///Function call for eat

        printf("philosoher %d leaving fork %d and %d\n",(*temp+1),(*temp + 1), (LEFT + 1));
        sem_post(&sem[*temp]);               ///Release of corresponding fork
        sem_post(&sem[((*temp + 1) % SIZE)]);///Release of next fork

        sleep(2);                       ///To invoke other hungry philosophers
    }
}

int main()
{
    int iter;
    int ret;
    pthread_t tid[SIZE];

    for(iter = 0; iter < SIZE; iter++)
        sem_init(&sem[iter], 0, 1);

    for(iter = 0; iter < SIZE; iter++)  ///Creation of philosopher threads
    {
        ret = pthread_create(&tid[iter], NULL, philosopher_loop, &philosopher[iter]);
        assert(!ret);
    }
    pthread_exit(NULL);
}

