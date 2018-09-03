
/**
 * File              : my_atoi.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 25.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function to convert ascii to integer value
 * \param str is a string
 * \return Returns integer value on success and -1 on error
 * */
int my_atoi(char *str)
{
    int temp = MIN;
    int value;

    while ((*str != '\0') && (*str != '\n')) {  /* Looping till null
						   character */
	if (((*str) < 48) || ((*str) > 57)) {   /* Checking for positive
						   integer values */
	    printf("Invalid input value\n");
	    return INVALID;
	}

	value = *str - 48;
	temp = (temp * 10) + value;
	str++;
    }
    return temp;
}
