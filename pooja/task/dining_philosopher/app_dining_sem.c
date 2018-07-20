/** Dining philosopher program*/
//@author Poojashree M
//@date 18/07/18
//@brief : Dining philosopher solution using mutex and semaphore

///inclusion of header file
#include "header.h"

/// Global variables defined ..
int philosophers[NUM] = {0, 1, 2, 3, 4};		///Number of philosophers
int right = 0;
int left = 0;


void *philosopher_fn(int phil_num)
{
	while(1){
		printf("Philosopher %d is THINKING\n", phil_num+1);
		sleep(2);
		take_fork(phil_num);						///function call to pick the fork
		sleep(2);									
		place_fork(phil_num);						///function call to place the fork again
	}
}

///Function to pick the forks 
void take_fork(int phil_num)
{
	pthread_mutex_lock(&mtx);
	state[phil_num] = HUNGRY;						///state of philosopher is hungry
	printf("Philosopher %d is HUNGRY\n", phil_num+1);
	check_avail_fork(phil_num);						///has to check availability of left and right forks
	pthread_mutex_unlock(&mtx);
	sem_wait(&sem[phil_num]);
}

///Function to check availability of left and right forks
void check_avail_fork(int phil_num)
{
	right = (phil_num == 0)? NUM-1 : phil_num - 1;
	left = (phil_num == NUM-1)?0:phil_num+1;

	if((state[phil_num] == HUNGRY) && (state[left] != EATING) && (state[right] != EATING)){			/**check state of philosopher is hungry,
																										left and right forks are available*/
		state[phil_num] = EATING;																						

		printf("Forks taken %d and %d by philosopher %d\n", right+1, phil_num+1, phil_num+1);
		printf("Philosopher %d is EATING\n", phil_num +1);

		sem_post(&sem[phil_num]);
	}
}

///Function definition to place the forks back
void place_fork(int phil_num)
{
	pthread_mutex_lock(&mtx);
	right = (phil_num == 0)? NUM-1 : phil_num - 1;
	left = (phil_num == NUM-1)?0:phil_num+1;

	state[phil_num] = THINKING;

	printf("Forks %d and %d are placed again by philosopher %d\n",right+1, phil_num+1, phil_num+1);
	printf("Philosopher %d is again THINKING\n", phil_num+1);

	check_avail_fork(left);												///has to check availability of forks for left philosopher
	check_avail_fork(right);											///has to check availability of forks for right philosopher
	pthread_mutex_unlock(&mtx);
}

/// Creates threads depending on number of philosophers
int main()
{
	pthread_t th_id[5];
	int status = 0;
	int index = 0;

	sem_init(&sem_main, 0 , 1);
	for(index = 0; index < NUM; index++){
		sem_init(&sem[index], 0, 0);
	}

	for(index = 0; index < NUM; index++){
		status = pthread_create(&th_id[index], NULL, (void *)philosopher_fn, (void *)philosophers[index]);					///creation of threads
		if(status != 0){
			perror("Pthread:%s\n");
		}
	}
	pthread_exit(NULL);
	return 0;
}
