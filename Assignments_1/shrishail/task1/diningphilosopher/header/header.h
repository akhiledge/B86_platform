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
#define SIZE 6
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
sem_t S[SIZE];
int state[SIZE]; /*!@ state is an array of SIZE*/
//int phil[SIZE] = {0, 1, 2, 3, 4, 5};
void philosophertest(int pnum);
void takechop(int pnum);
void putchop(int pnum);
void* philosopher(void* num);

