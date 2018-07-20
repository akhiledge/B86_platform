#include "header1.h"
void *philosopher_fn(int phil_num)
{
	printf("Philosopher %d is thinking\n", phil_num+1);
	sleep(2);
	take_fork(phil_num);
	place_fork(phil_num);
}
///Function to take the forks 
void take_fork(int phil_num)
{
	pthread_mutex_lock(&mtx);
	state[phil_num] = HUNGRY;
	printf("Philosopher %d is hungry\n", phil_num+1);
	check_avail_fork(phil_num);
	pthread_mutex_unlock(&mtx);
	
}
///Function to check availability of left and right forks
void check_avail_fork(int phil_num)
{
	right = (phil_num + (NUM - 1)) % NUM;
	left = (phil_num + 1) % NUM;

	if((state[phil_num] == HUNGRY) && (state[left] != EATING) && (state[right] != EATING)){
		state[phil_num] = EATING;
		printf("Philosopher %d is eating\n", phil_num+1);
		printf("Forks taken %d and %d by philosopher %d\n", right+1,left, phil_num+1);
//		sleep(2);
	}	

}
///Function definition to place the forks back
void place_fork(int phil_num)
{
	pthread_mutex_lock(&mtx);
	right = (phil_num + (NUM - 1)) % NUM;
	left = (phil_num + 1) % NUM;
	state[phil_num] = THINKING;

		printf("Forks  %d and %d are placed back by philosopher %d\n", right+1, left, phil_num+1);
	printf("philosopher %d is again thinking\n", phil_num+1);

	check_avail_fork(left);
	check_avail_fork(right);
	pthread_mutex_unlock(&mtx);
}
/// Creates threads depending on number of philosophers
int main()
{
	pthread_t th_id[5];
	int status = 0;
	int index = 0;

	for(index = 0; index < NUM; index++){
		sem_init(&sem[index], 0, 0);
	}

	for(index = 0; index < NUM; index++){
		status = pthread_create(&th_id[index], NULL, philosopher_fn, philosophers[index]);
		num = philosophers[index];
		if(status != 0){
			perror("Pthread:%s\n");
		}
	}
	
		pthread_exit(NULL);
		return 0;
}
