
/**
 * File              : hash_index.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to find hash table index value
 * \param ch is a character storing first character of word
 * \return Returns index value(0-25) on success and -1 on error
 * */
int hash_index(char ch)
{
    switch (ch) {
	case 'A'...'Z':
	    return ch - 65;
	case 'a'...'z':
	    return ch - 97;
	default:
	    return INVALID;
    }
}
