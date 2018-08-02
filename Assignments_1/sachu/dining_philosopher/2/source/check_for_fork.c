extern int state[SIZE];
extern sem_t sem[SIZE];
/*
 * @brief Function definition to check for fork availability
 * @param value is philosopher index
 * */
void check_for_fork(int value)
{
    if(state[value] == HUNGRY)  ///checking state
    {
        if(state[LEFT_P] != EATING && state[RIGHT_P] != EATING) ///checking state of left and right philosopher
        {
        state[value] = EATING; ///Changing state
        printf("Philosopher %d aqcuired forks %d and %d\n",(value + 1),LEFT_P  + 1, value + 1);

//        sleep(1);
        printf("Philosopher %d started eating\n", (value + 1));
  //      sleep(2);

        sem_post(&sem[value]); ///Semaphore post to indicate fork acquisition
    }
    }
}
