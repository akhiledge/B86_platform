/**
 * File              : modify_string.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 23.09.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief: To remove \n appended to the input taken from fgets
 *@param: str is the word read from file
 *return: void
 */
void modify(char *str)
{
	while (*str) {
		if (*str == '\n') {
		*str = '\0';
		}
		str++;
	} 
}
