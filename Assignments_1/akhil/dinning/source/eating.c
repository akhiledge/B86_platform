/**
 * File              : dinning/source/eating.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
#include "./../header/standard.h"
#include "./../header/dinners.h"

/**
 * @Synopsis  eating_food is function which takes care of food variable
 *
 * @Param position
 *
 * @Returns bool
 */
bool eating_food (int32_t position )
{
    struct timespec wait_time = {.tv_sec = MIN_TIM, .tv_nsec = MAX_TIM};
    int32_t status = 0;
    status = sem_timedwait ((sprocess + position), &wait_time);
    if (-1 == status )
        return false;
    status = sem_timedwait (sprocess + ((position + 1) % phil_on_table),\
                     &wait_time);
    if (-1 == status){
        status = sem_post (sprocess + position);
        if(-1 == status)
        printf("%s", strerror(errno));
        return false;
    } 
    wait_time.tv_sec = (position + 1);
    printf ("Philosopher %d on table eating\t"\
          " food status is %d \n", position + 1,food); 
    food--;    //** total food given to eat 
    printf("Remaining food is %d\n",food); 
    usleep ((useconds_t)wait_time.tv_nsec); 
    printf ("Philosopher %d done eating"\
            "\tfood status is %d \n", position + 1, food);
    status = sem_post (sprocess + position);
    
    if (-1 == status)
        printf("sem_post failed : %s", strerror(errno));

    status = sem_post (sprocess + ((position + 1) % phil_on_table));
    
    if (-1 == status) 
        printf("sem_post failed : %s", strerror(errno));
    return true;
}
