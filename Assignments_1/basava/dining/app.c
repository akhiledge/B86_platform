/** Dining Philosopher problem application using semaphores */

///header file inclusion
#include "header.h"

///global variable definitions
int phil_arr[NUM_PHIL] = {0, 1, 2, 3, 4};
volatile int food_count = FOOD_COUNT;

///Thread definition

void *philosopher (void *ptr)
{
    /**since there are 5 philosophers all has to be synchronized to eat*/

    while (TRUE){      //continuos till everyone eat
        ///variable declarations
        int *phnum = NULL; 
        phnum = (int *) ptr;

        sleep (TRUE);
        take_the_spoon (*phnum); //both left and right spoon has to take
        sleep (FALSE);
        put_back_spoon (*phnum); //after eating put the spoons back
        if (food_count == FALSE){
            exit (0);
        }
    }
}
///main function definition

int main (void)   
{
    ///variables Initializations

    sem_init (&sem, THREAD, INIT_VAL_SEM);  //initialise the locking semaphore
    int index = INIT_VAL;
    int status = INIT_VAL;
    pthread_t th[NUM_PHIL];    //thread for each philosopher

    while (index < NUM_PHIL){       //semaphore for each philosopher initialise to 0
        sem_init (&sem_val[index], THREAD, INIT_VAL);
        index++;
    }

    for (index = INIT_VAL; index < NUM_PHIL; index++){  //creating a threads as philosopher                                                          
        status = pthread_create (&th[index], NULL, philosopher, &phil_arr[index]);

        if (status < FALSE){
            fprintf (stdout, "%d\n thread creation failed\n", index);
        }
        fprintf (stdout, "%d philosopher is waiting\n", index + TRUE );
    }   

    index = INIT_VAL;

    while (index < NUM_PHIL){      //main thread waiting for all sub threads
        pthread_join (th[index], NULL);
        index++;
    }
    return INIT_VAL;
}
