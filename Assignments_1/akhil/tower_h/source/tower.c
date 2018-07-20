/**
 * File              : source/tower.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */

#include "./../header/standard.h"
#include "./../header/tower.h"



void hanoi_tower(int32_t disc, char source, char destiny, char middleman ){

    if(disc==1)                                                                
    {                                                                           
            printf("%10d | %-5c | %-5c |\n",1,source,destiny);

            return; 

    }                                                                         
    else                                                                        
    {                                                                           
            hanoi_tower (disc-1, source, middleman, destiny);                

            printf("%10d | %-5c | %-5c |\n",disc, source, destiny);       

            hanoi_tower (disc-1, middleman, destiny, source);

    }                                                                       

}    
