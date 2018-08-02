/**
 * File              : regular_phil.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
#include "./../header/standard.h"
#include "./../header/dinners.h"
void * regular_work_of_phil (void * phil_place ) {
    
    bool ate_full = false;
    
    int position = 0;
    
    position = ((pthread_t *)phil_place - thread);
    
    while (food > 0){
    
        printf("\t\t\tfood remain is %d\n",food);
    
        thinking_about_food (position);
    
        printf ("Philosopher %d is hungry \n ", position + 1);
        
        while (!ate_full && (food > 0)){
    
            ate_full = eating_food (position);
        }
        if(!(food > 0)) {
        
        printf ("Philosopher %d is hungry and food is not available \n ",\
                position + 1);
            
        }     
        ate_full = false;
    
    }
    return NULL;
}


