/** Dining philosophers problem */

///header guards]
#ifndef HEADER_H
#define HEADER_H

///header file inclusion
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

///macro definitions
#define NUM_PHIL 5
#define WAIT 2
#define DESPARATE 1
#define EAT 0
#define THREAD 0
#define INIT_VAL_SEM 1
#define INIT_VAL 0
#define TRUE 1
#define FALSE 0
#define FOOD_COUNT 10
#define LEFT ((phnum + NUM_PHIL) % NUM_PHIL)
#define RIGHT ((phnum + TRUE) % NUM_PHIL)

///function and variable declarations
int state_phil[NUM_PHIL];
sem_t sem_val[NUM_PHIL];
sem_t sem;
void *philosophers (void *ptr);
void take_the_spoon (int phnum);
void put_back_spoon (int phnum);
void test_leftnright (int phnum);

///end of header guard
#endif
