/**
 *
 *  File name           : Diners_philosphers.c
 *  Author              : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  File Creation       : 16-07-2018
 *  Created by          : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  Last modification   : 19-07-2018
 *  Last modified by    : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *
 * **/


////    Header files

#include <stdio.h>        
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define MAX 5              //// Maximum value for philosphers and  Semaphores

///Different states of the philosopher Eating, Hungry and Thinking
#define EAT 0    
#define HUNGRY 1
#define THINK 2


#define P_MAX 20

int Philospher[P_MAX] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};        //// Array of Philosphers 
int State[MAX];             //// State of the Philospher with their of respective index

sem_t Semaphore[MAX];       //// Array of Semaphores 
sem_t Mutex;                //// common semaphore 



void Check(int Philospher_num)
{
    int left = (Philospher_num + (MAX-1)) % MAX;
    int right = (Philospher_num + 1) % MAX;

    //// check the state of the philosopher_num and his left & right philosophers states.
    if(State[Philospher_num] == HUNGRY && State[left] != EAT && State[right] != EAT){
        //// state that eating.
        State[Philospher_num] = EAT;
        sleep(2);

        printf("Philospher %d is taking forks %d and %d\n", Philospher_num + 1, left+1, Philospher_num + 1);
        printf("Philospher %d is Eating\n", Philospher_num + 1);  
        ////sem_post don't have any effect when taking the fork and it is used wake up the hungry philosopher.
        sem_post(&Semaphore[Philospher_num]);
    }
    return;
}



///// Take the fork

void Taking_fork(int Philospher_num)
{
    sem_wait ( &Mutex );

    printf("Philospher %d is hungry\n", Philospher_num + 1);
    /// state that philosopher is hungry.
    State[Philospher_num] = HUNGRY;
    /// check if neighbours are eating or not, if not eat.
    Check(Philospher_num);

    sem_post ( &Mutex );
    /// if unable to eat wait untill the signal comes
    sem_wait ( &Semaphore[Philospher_num] );
    sleep(1);

    return;
}


//// Put the forks down

void Puting_fork(int Philospher_num)
{
    int left = (Philospher_num + (MAX-1)) % MAX;
    int right = (Philospher_num + 1) % MAX;

    sem_wait ( &Mutex );

    //// state that thinking.
    State[Philospher_num] = THINK;
    printf("Philospher %d is putiing forks %d and %d down\n", Philospher_num + 1, left +1, Philospher_num +1); 
    printf("Philospher %d is thinking\n", Philospher_num + 1);

    Check (left);
    Check (right);

    sem_post ( &Mutex );

    return;
}


//// Philosphers function

static void *Philosphers( void *num)
{
    //while(true){
        int *index = num;
        ////state that philosopher is in thinking
    State[*index] = THINK;
        sleep(2);
        Taking_fork(*index);
        sleep(1);
        Puting_fork(*index);
   // }
    return NULL;
}


int main(void)
{
    int index;

    pthread_t Thread[MAX];

    sem_init(&Mutex, 0, 1); ///Initialize the common semaphore.

    for (index = 0; index < MAX; index++)           
          ////Initializing all the semaphores.
          sem_init ( &Semaphore[index], 0, 1 ); 

    for (index = MAX - 1; index >= 0; index--){
        /// Creating semaphore processes.
        pthread_create ( &Thread[MAX], NULL, &Philosphers, &Philospher[index]);
       ////Initially created philospher process is in thinking state. 
        printf("Philospher %d is Thinking\n", index+1);                 
    } 
    
    pthread_exit(NULL);
    return 0;
}
