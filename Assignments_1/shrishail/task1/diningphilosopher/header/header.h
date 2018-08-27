/**
 * File:header.h
 * Author:Shrishail satihal
 * Description:Dining philosopher problem
 * Date:23-8-18
 * Last modified:23-8-18
 */

/*
 * header Guard
 */
#ifndef _HEADER_H

/*
 * Header Guard
 */
#define _HEADER_H

/**
*@headerfile stdio.h
*/
#include <stdio.h>

/**
*@headerfile pthread.h
*/
#include <pthread.h>

/**
*@headerfile semaphore.h
*/
#include <semaphore.h>

/**
* @def SIZE
*/
#define SIZE 5

/**
* @def THINK
*/
#define THINK 2

/**
* @def HUNGRY
*/
#define HUNGRY 1

/**
* @def EAT
*/
#define EAT 0
sem_t sem; /*!@sem sem is variable of type sem_t*/
sem_t Semaphore[SIZE];
int state[SIZE]; /*!@ state is an array of SIZE*/

/**
 *function prototype for philosopher test which takes an argument philosopher\
number of type int and returns void 
 */
void philosophertest(int);

/**
 * function prototype for take chop which takes an argument philosophernumber\
 * of type int and returns void
 */
void takechop(int);

/**
 * function prototype for put chop which takes an argument philosophernumber\
 * of type int and returns void
 */
void putchop(int);

/**
 * function prototype for philosopher which takes an argument philosophernumber\
 * of type void and returns void pointer
 */
void *philosopher(void *);
#endif /* end of headerguard */
