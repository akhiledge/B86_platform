/** Inclusion of header files and definitiion of macros*/
///Header guard
#ifndef HEADER1_H
#define HEADER1_h

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 5									///Macro definition for number of philosophers
enum state_phil{THINKING, HUNGRY, EATING};		///States the philosophers can be in
int philosophers[NUM] = {0, 1, 2, 3, 4};		///Number of philosophers
int state[NUM];									///Variable to hold state of each philosopher
sem_t sem[NUM];									///semaphore
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	///mutex
int left = 0;
int right = 0;

///Function declarations
void *philosopher_fn(int);
void take_fork(int);
void check_avail_fork(int);
void place_fork(int);

///End of header guard
#endif

