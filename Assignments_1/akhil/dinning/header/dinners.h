/**
 * File              : ../header/dinners.h
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 14.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */

/**
 *
 * @about : Project related prototypes and external variables
 *
 **/

#ifndef __DINNER_H_
                        //Header Guard
#define __DINNER_H_

// Macros 

#define BUFSIZ_MAX 128

#define SEM_FULL 251

#define MIN_TIM 1254554

#define MAX_TIM 63533

#define BIN_ONE 1

#define BIN_ZERO 0
//Macros end .....

// External variables
extern uint32_t phil_on_table;

extern int32_t food;


extern sem_t * sprocess;

extern pthread_t * thread;


// External variables end .....

// Prototypes 
 extern bool eating_food (int position );

 extern bool destroy_sprocess (int position );
 
 extern bool create_sprocess (void );
 
 extern bool thinking_about_food (int position );
 
 extern void * regular_work_of_phil (void * phil_place );







// Prototypes end .....


#endif
