/**
 * File              : main.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
#include "./../header/standard.h"
#include "./../header/dinners.h"

/**
 *
 * Definition of global varibales should be always in main.c
 *
 **/
uint32_t phil_on_table;
int32_t food;
sem_t *sprocess;
pthread_t *thread;

int main(int argc, char **argv)
{

    int status = 0;
    int position = 0;

    /**
     * From command line arguments data retriving is done
     *
     **/
    if (argc < 3) {
	printf("Wrong commad line arguments Entered : %s\n", strerror(EINVAL));
	return 0;
    } else {
	    phil_on_table = atoi(argv[1]);
	    food = atoi(argv[2]);
	    sprocess = (sem_t *)malloc(sizeof(sem_t) * phil_on_table);
	    assert(sprocess);
	    thread = (pthread_t *)malloc(sizeof(pthread_t) * phil_on_table);
	    assert(thread);
    }

    /**
     *
     * Input is taken care and now the process starts
     *
     **/

    status = create_sprocess();

    if (-1 == status) {
	printf("Semaphore not created : %s\n", strerror(errno));
	return 0;
    }

    while (position < phil_on_table) {
	pthread_create(thread + position, NULL, regular_work_of_phil,\
		(thread + position));
	pthread_detach(*(thread + position));
	position++;
    }

    pthread_exit(NULL);
    return 0;
}

