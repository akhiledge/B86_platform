
/**
 * File              : philosopher_fun.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 17.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function for philosopher
 * \param value is void pointer
 * */
void *philosopher_fun(void *value)
{
    int *iter;

    while (1) {
	iter = (int *) value;

	fork_acquire(*iter);        /* Function call for acquiring fork */
	fork_release(*iter);        /* Function call for releasing fork */
    }
}
