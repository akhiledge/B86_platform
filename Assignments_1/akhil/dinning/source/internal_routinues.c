/**
 * File              : internal_routinues.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
 #include "./../header/standard.h"
 #include "./../header/dinners.h"

/**
 * @Synopsis  destroy_sprocess will destroy the semaphore 
 *
 * @Param position will determine the semaphore which has to be destroyed
 *
 * @Returns   bool
 */
bool destroy_sprocess (int position )
{
    while (position-- >= 0){
        if (-1 == sem_destroy (sprocess + position))
            printf("semaphore destroy failed : %s \n",strerror(errno));
    }
    return true;
}/** End of the destroy_sprocess function */

/*semaphore creation for each fork*/
/**
 * @Synopsis  creating thread
 *
 * @Returns   bool
 */
bool create_sprocess (void )
{
    int position = 0;   /**@Var position determines the state of process */
    int status = 0;     /**@var status determines the status of various
                                Inbuilt functions */


    while (position < phil_on_table){
            /**@Synopsis Initializing the semaphores */
        status = sem_init ( (sprocess + position), BIN_ZERO, BIN_ONE);

        if (-1 == status){
            (position > 0) ? destroy_sprocess ( position ) : true;
            return false;
        }
        position++;
    }
    return true;
}/** End of the create_sprocess function */
