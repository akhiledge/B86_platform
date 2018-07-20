/*
 * @brief header_file
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
/*
 * @brief Macros defined for states
 * */
#define THINKING 0
#define HUNGRY 1
#define EATING 2

#define SIZE 5 ///Macro SIZE defined

/*
 * @brief Macro definition to find philosopher numbers
 * */
#define LEFT_P (value + (SIZE - 1)) % SIZE
#define RIGHT_P (value + 1) % SIZE

///Function prototypes
void *philosopher_fun(void *value);
void fork_acquire(int value);
void check_for_fork(int value);
void fork_release(int value);

