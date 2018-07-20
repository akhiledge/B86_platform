/**
 * File              : thinking.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
 
#include "./../header/standard.h"
#include "./../header/dinners.h"

bool thinking_about_food (int32_t position ){
    
    
        printf (" Philosopher %d thinking about fooding"\
               "\t Food remaining is %d \n", position + 1, food);
            
        usleep ((useconds_t) MIN_TIM );

                return true;
}
