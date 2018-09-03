/**
 * File              : header.h
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 18.07.2018
 * Brief			 : Header file for dining semaphore
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**Header guard*/
#ifndef HEADER_H
#define HEADER_H

/**Header file inclusion*/
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 5 /*!@def : Macro definition for number of philosophers*/
enum state_phil {THINKING, HUNGRY, EATING}; /**States the philosophers
											 can be in*/

int state[NUM];	/*!@Var: variable to hold state of each philosopher*/
sem_t sem_main;
sem_t sem[NUM];	/*semaphore*/
extern int right;
extern int left;

/**Function declarations*/
void *philosopher_fn(void *);
void take_fork(int);
void check_avail_fork(int);
void place_fork(int);

/**End of header guard*/
#endif

