/**
 * File              : my_atoi.c
 * Author            : Basava Prasad S J
 * Date              : 20.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Basava Prasad S J
 */
/** @brief : my_atoi implementation  to convert ASCII values into integer */

/**Header file inclusion */
#include "rbt_header.h"

/**@param : string (ASCII) to convert into integer
 *@return : Integer obtained after conversion
 */

int my_atoi (char *str)
{
    /**variable declarations*/
    int number = 0;                                     /*to return the 
                                                          integer*/
    int index = 0;

    while (*(str + index) != '\n'){                     /*continuos loop untill 
                                                          the end of string*/
        number = (number * 10) + (*(str + index) - '0');/*integer extraction*/
        index++;
    }
    if (*(str + 0) == '-'){                             /*if entered number is 
                                                          negative*/
        return 0;
    }
    return number;                                      /*return the integer 
                                                          converted value*/
}
