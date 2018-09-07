
/**
 * File              : hash_tab_function.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 23.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**@brief:Hash function to get index from key
 *@param: first character of the word
 *@return: returns index of type int
 */

int hash_func(char ch)
{
	if ((ch >= 'a') && (ch <= 'z')) {			/**if initial character is
											  lowercase*/
		return (ch - 'a');					/**index is (ch - 97)*/
	}
	else if ((ch >= 'A') && (ch <= 'Z')) {	/**if initial character is
											uppercase*/
		return(ch - 'A');					/**index is (ch - 65)*/
	}
	else if ((ch >= '0') && (ch <= '9')) {	/**if initial character is
											  number*/
		return(ch + 26 - '0');
	} else {								/**special characters*/
		return 37;
	}

}
