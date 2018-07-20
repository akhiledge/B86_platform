//#include"header.h"
//int phil[SIZE] = {0, 1, 2, 3, 4, 5};
void philosophertest(int pnum)
{
                //check whether philosopher is in hungry state
                //check whether right and left handside philosopher are eating or not
                if (state[pnum] == HUNGRY && state[(pnum+SIZE-1)%SIZE] != EAT && state[(pnum+1)%SIZE] != EAT) {
                                state[pnum] = EAT;
                                printf("philosopher %d took chopsticks  %d and %d\n",   pnum + 1, ((pnum+1)%SIZE) + 1, pnum + 1);
                                printf("philosopher %d is Eating\n", pnum + 1);
                                sem_post(&S[pnum]);
                }
}


void takechop(int pnum)
{
                sem_wait(&sem);
                state[pnum] = HUNGRY;
                printf("philosopher %d is Hungry now\n", pnum + 1);
                //function call for philosopher 
                philosophertest(pnum);
                sem_post(&sem);
                sem_wait(&S[pnum]);
}

void putchop(int pnum)
{
sleep(1);
                sem_wait(&sem);
                state[pnum] = THINK;
                printf("philosopher %d keeping chopsticks %d and %d to down\n",pnum + 1, ((pnum+SIZE-1)%SIZE) + 1, pnum + 1);
                printf("philosopher %d is thinking\n", pnum + 1);

                philosophertest((pnum+SIZE-1)%SIZE);
                philosophertest((pnum+1)%SIZE);

                sem_post(&sem);
}

void* philosopher(void* num)
{
                int* index = num;
                sleep(1);
                //function call for philosopher to take a chopstick
                takechop(*index);
        //      sleep(1);
                //function call for philosopher to put chopstick
                putchop(*index);
}

