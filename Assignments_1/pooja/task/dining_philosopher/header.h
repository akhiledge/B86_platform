/** Inclusion of header files and definitiion of macros*/
///Header guard
#ifndef HEADER_H
#define HEADER_h

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 5									///Macro definition for number of philosophers
enum state_phil{THINKING, HUNGRY, EATING};		///States the philosophers can be in
=======
int state[NUM];									///Variable to hold state of each philosopher
sem_t sem[NUM];									///semaphore
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	///mutex
extern int right ;
extern int left ;


///Function declarations
void *philosopher_fn(int);
void take_fork(int);
void check_avail_fork(int);
void place_fork(int);

///End of header guard
#endif

