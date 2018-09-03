/**
 * File              : modify_string.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 26.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Function definition to remove \n character
 * \param str is a character pointer storing base address of string
 * */
void modify_string(char *str)
{
    int len = strlen(str) - 1;  /*To check for ',' or '.' or
				  '\n' character */
    if ((str[len] == '.') || (str[len] == ',') || (str[len] == '\n')) {
	while ((*str != '\n') && (*str != '\0') && (*str != ',') &&
		(*str != '.')) {
	    str++;
	}
	*str = '\0';
    }
}
