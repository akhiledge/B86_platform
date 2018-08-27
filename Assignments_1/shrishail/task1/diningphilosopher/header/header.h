
/*
 * File:header.h
 * author:shrishail satihal
 * Description:dining philosopher problem
 * date:23-8-18
 * Last modified:23-8-18
 */

/*
 * Header Guard
 */
#ifndef _HEADER_H

/*
 * Header Guard
 */
#define _HEADER_H

/*
 *@header pthread.h
*/
#include<pthread.h>

/*
 *@header semaphore.h
*/
#include<semaphore.h>

/*
 *@header stdio.h
 */
#include <stdio.h>

/*
 *@ def SIZE 5
 */
#define SIZE 5

/*
 *@def THINKING 2
 */
#define THINKING 2

/*
 *@def HUNGRY 1
 */
#define HUNGRY 1

/*
 *@def EATING 0
 */
#define EATING 0

/*
 *@def LEFT (phnum + SIZE - 1) % SIZE
 */
#define LEFT ((phnum + SIZE - 1) % SIZE)

/*
 *@def RIGHT (phnum + 1) % SIZE
 */
#define RIGHT ((phnum + 1) % SIZE)

int state[SIZE];
sem_t sem; /*!@sem is variable of type sem_t*/
sem_t Semaphore[SIZE]; /*!@ state is an array of SIZE*/

/*
 * function prototype for philosopher
 */
void *philosopher(void *);

/*
 * function prototype for put fork
 */
void put_fork(int);

/*
 * function prototype for take fork
 */
void take_fork(int);

/*
 * function prototype for philosopher test
 */
void philosopher_test(int);
#endif///end of header guard
