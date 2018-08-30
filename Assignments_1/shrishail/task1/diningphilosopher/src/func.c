
/*
 * File:func.c
 * author:shrishail satihal
 * Description:dining philosopher problem
 * date:23-8-18
 * Last modified:23-8-18
 */
void
philosopher_test(int phnum)	/*function definition to test philosopher
				   which takes arguments philosopher number
				   of type integer and returns void */
{
  if (state[phnum] == HUNGRY && state[LEFT] != EATING
      && state[RIGHT] != EATING) {
				/*check whether philosopher is
				   in hungry state and right and left
				   hand side philosophers are eating
				   or not */
      state[phnum] = EATING;	/*state that eating */
      printf("Philosopher %d takes fork %d and %d\n",
	      phnum + 1, LEFT + 1, phnum + 1);
      printf("Philosopher %d is Eating\n", phnum + 1);
      sem_post(&Semaphore[phnum]);
    }
}				/*end of philosophertest function */

void
take_fork(int phnum) /*function definition for taking fork which takes
				   arguments philospher number of type integer and
				   returns void */
{
  sem_wait(&sem);
  state[phnum] = HUNGRY;	/*state that hungry */
  printf("Philosopher %d is Hungry\n", phnum + 1);
  philosopher_test(phnum);	/*eat if neighbours are not eating */
  sem_post(&sem);
  sem_wait(&Semaphore[phnum]);
  sleep(1);
} /*end of take fork function */

void
put_fork(int phnum)	/*function definition for putting fork which takes
				   argument philospher number of type integer which
				   returns void */
{
  sem_wait(&sem);
  state[phnum] = THINKING;	/*state that thinking */
  printf("Philosopher %d putting fork %d and %d down\n",
	  phnum + 1, LEFT + 1, phnum + 1);
  printf("Philosopher %d is thinking\n", phnum + 1);
  philosopher_test(LEFT);
  philosopher_test(RIGHT);
  sem_post(&sem);
} /*end of put forkfunction */

void *
philosopher(void *num) /*function definition for philospher which takes
				   phiosopher num of type void and returns void */
{
  int *index = num;

  sleep(1);
  take_fork(*index);
  put_fork(*index);
} /*end of philosopher function */
