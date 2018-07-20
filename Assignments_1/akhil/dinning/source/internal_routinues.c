/**
 * File              : internal_routinues.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
 #include "./../header/standard.h"
 #include "./../header/dinners.h"

bool destroy_sprocess (int position ){
    
    while (position-- >= 0){
    
        if (-1 == sem_destroy (sprocess + position))

            printf("semaphore destroy failed : %s \n",strerror(errno));

    }

    return true;

}

/*semaphore creation for each fork*/
bool create_sprocess (void ){

    int position = 0;
    int status = 0;

    while (position < phil_on_table){

        status = sem_init ( (sprocess + position), BIN_ZERO, BIN_ONE);

        if (-1 == status){

            (position > 0) ? destroy_sprocess ( position ) : true;

            return false;

        }

        position++;

    }

    return true;
}

