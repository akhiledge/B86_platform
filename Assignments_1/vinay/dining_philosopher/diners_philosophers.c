/**
 * \file diners_philosophers.c
 * \brief Dining philosophers problem.
 * Each philosopher will think for a time of their index (for expample 
 * philosopher 2 will think for two seconds) and then go for eating.
 */

#include <stdio.h> 
#include <stdbool.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <semaphore.h> 
#include <errno.h> 
#include <time.h> 
#include <pthread.h> 

#define  PHILOSOPHERS 4                 /**< number of philosophers*/ 
#define  SHARED 0                       /**< semaphore shared between threads*/ 
#define  BINARY 1                       /**< binary semaphore initial value*/ 

static pthread_t th[PHILOSOPHERS];      /**< array of philosophers using threads*/ 
static sem_t sem_fork[PHILOSOPHERS];    /**< array of semaphore for each fork*/ 
time_t philosophers_time[PHILOSOPHERS]; /**< endtime of eating*/ 
static time_t start;                    /**< time before creation of a thread*/ 
int iterations;                         /**< number of routines a philosopher 
                                          has to perform*/ 

/**\brief semaphore cleanup (i.e., destrying semaphores) while one of semaphore 
 * creation failed
 * \param index number of semaphores need to destroyed*/ 
bool clean_sem (int index){
    while (index-- >= 0){
        if (-1 == sem_destroy (sem_fork + index))
            perror ("semaphore destroy");
    }
    return true;
}

/**\brief semaphore(unnamed) creation for each fork*/ 
bool create_forks_to_eat (void){
    int index = 0;                      /**< index of a semaphore in sem_fork[]*/ 
    int status = 0;                      
    while (index < PHILOSOPHERS){
        status = sem_init ( (sem_fork + index), SHARED, BINARY); 
        if (-1 == status){
            (index > 0) ? clean_sem (index) : true;
            return false;
        }
        index++;
    }
    return true;
}

/**\brief eat routine for a philosopher
 * \param index index of philosopher*/
bool eat (int index){
    struct timespec wait_time = {.tv_sec = 1};/**< wait time for a fork 
                                                availability*/ 
    int status = 0;

    status = sem_timedwait ((sem_fork + index), &wait_time);/** wait for fork */ 
    if (-1 == status)                       /** not available return*/ 
        return false;
    status = sem_timedwait (sem_fork + ((index + 1) % PHILOSOPHERS), &wait_time);
                                            /**  wait for other fork*/ 
    if (-1 == status){                      /** not available release obtained
                                              fork*/ 
        status = sem_post (sem_fork + index);
        if (-1 == status)
            perror ("sem_post failed\n");
        return false;
    }

    printf ("Philosopher %d eating \n", index + 1); 
    nanosleep (&wait_time, NULL);           /** eat for a time*/ 
    printf ("Philosopher %d done eating after %f\n", index + 1,\
            difftime (time(philosophers_time + index), start)); 
    status = sem_post (sem_fork + index);  /** release the forks obtained*/ 
    if (-1 == status)
        perror ("sem_post failed\n");
    status = sem_post (sem_fork + ((index + 1) % PHILOSOPHERS));
    if (-1 == status)
        perror ("sem_post failed\n");
    return true;
}

/** \brief think routine of a philosopher
 * \param index index of philosopher*/ 
bool think (int index){
    printf ("I'm (Philosopher %d) thinking \n", index + 1); 
    struct timespec think_time = {.tv_sec = index};/**< think time*/ 
    nanosleep (&think_time, NULL);          /** thinking*/ 
    return true;
}

/**\brief philosopher routine
 * think for a time (their index seconds), eat and repeat
 * \param philosopher_addr thread address of philosopher to calculate his index
 **/
void *philosopher_routine (void *philosopher_addr){
    bool done_eating = false;               /**< flag to verify that 
                                              a philosopher has ate or not*/ 
    int index = 0;                          /**< index of a philosopher*/ 
    int no_of_routines = iterations;        /**< no of routines left*/ 
    index = ((pthread_t *)philosopher_addr - th);
    while (no_of_routines--){               /** routine*/ 
    think (index);                          /** think*/ 
    printf ("Philosopher %d is hungry \n ", index + 1); 
    while (!done_eating){                   /** eat until done eating in 
                                              current iteration*/ 
        done_eating = eat (index);
    }
    done_eating = false;
    }
    return NULL;
}


int main (void) {

    int status = 0;                    
    int index = 0;                          /**< index of thread*/ 
    char *input_str = NULL;                 /**< input string from user*/ 

    status = create_forks_to_eat ();         
    if (-1 == status){
        perror ("semaphore creation failed\n");
        return 0;
    }

    input_str = (char *) calloc (1, sizeof (char) * BUF_SIZE);
    if (NULL == input_str){
        perror ("memory allocation failed\n");
        return 0;
    }


    while (0 != iterations){
        fputs ("Enter number of routines a philosopher has to perform(>0)\n",\
                stdout);
    iterations = atoi (fgets (input_str, BUF_SIZE, stdin));
    }

    free (input_str);
    input_str = NULL;

    time (&start);                          /** start of timer*/ 
    while (index < PHILOSOPHERS){
        pthread_create (th + index, NULL, philosopher_routine, (th + index));
        //pthread_detach (th[index]);
        index++;
    }
   pthread_exit (NULL); 
    return 0;
}
