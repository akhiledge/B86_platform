/************
 * Diner's philosophers problem
 *************/
/*using named semaphores*/ 
#include <stdio.h> 
#include <stdbool.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <semaphore.h> 

#define  PHILOSOPHERS 5 /*number of philosophers*/ 
#define  tok(x, y) x##y /*token pasting*/ 
#define  SEM_NAME(y) tok("/sem", y) /*semaphore name with number*/ 
#define  BINARY 1 /*binary semaphore initial value*/ 

static pthread_t th[PHILOSOPHERS]; /*array of philosophers using threads*/ 
static sem_t sem_fork[PHILOSOPHERS];/*array of semaphore for each fork*/ 

bool create_forks (void){/*semaphore creation for each fork*/ 
    int i = 0;
    while (i < PHILOSOPHERS){
       sem_fork[i] = sem_open (SEM_NAME (i), O_CREAT, 0666, BINARY); 
       if (SEM_FAILED == sem_fork[i]){
           (i > 0) ? cleanup (i) : true;
           return false;
       }
    }
    return true;
}

void *think (void *philosopher){
    return NULL;
}

int main (void) {

    int i = 0;
    return 0;
}
