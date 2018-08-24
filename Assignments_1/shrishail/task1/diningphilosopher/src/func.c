
/*
 * File:func.c
 * Description:Dining Philosopher problem
 * Date:23-8-18
 * Last modified:23-8-18
 */

void philosophertest(int pnum) ///Function prototype for Philosophertest which\
    takes an argument philosopher number of type integer and returns void pointer
{
    ///check whether philosopher is in hungry state
    ///check whether right and left handside philosopher are eating or not
    if (state[pnum] == HUNGRY && state[(pnum+SIZE-1)%SIZE] != EAT \
            && state[(pnum+1)%SIZE] != EAT) {
        state[pnum] = EAT;
        printf("philosopher %d took chopsticks %d and %d\n", pnum + 1, \
                ((pnum+1)%SIZE) + 1, pnum + 1);
        printf("philosopher %d is Eating\n", pnum + 1);
        sem_post(&Semaphore[pnum]);
    }
}


void takechop(int pnum) ///Function prototype for takechop which takes\
        an argument philosopher number of type integer and returns void 
{
    sem_wait(&sem);
    state[pnum] = HUNGRY;
    printf("philosopher %d is Hungry now\n", pnum + 1);
    philosophertest(pnum); ///function call for philosopher 
    sem_post(&sem);
    sem_wait(&Semaphore[pnum]);
}

void putchop(int pnum) ///Function prototype for putchop which takes\
        an argument philosopher number of type int and returns void 
{
    sleep(1);
    sem_wait(&sem);
    state[pnum] = THINK;
    printf("philosopher %d keeping chopsticks %d and %d to down\n", pnum + 1,\
            ((pnum+SIZE-1)%SIZE) + 1, pnum + 1);
    printf("philosopher %d is thinking\n", pnum + 1);
    philosophertest((pnum+SIZE-1)%SIZE);
    philosophertest((pnum+1)%SIZE);
    sem_post(&sem);
}

void* philosopher(void* num) ///Function prototype for Philosopher which takes\
        an argument philosopher number of type void and returns void pointer
{
    int* index = num;
    sleep(1);
    takechop(*index); ///function call for philosopher to take a chopstick
    putchop(*index); ///function call for philosopher to put chopstick
}

