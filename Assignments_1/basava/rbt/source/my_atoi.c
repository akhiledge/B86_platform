/** my_atoi implementation */

///Header file
#include "rbt_header.h"

/**atoi function definition */

int my_atoi (char *str)
{
    ///variable declarations
    int number = 0; //to return the integer
    int index = 0;

    while (*(str + index) != '\n'){  //continuos loop untill the end of string
        number = (number * 10) + (*(str + index) - '0'); //integer extraction
        index++;
    }
    if (*(str + 0) == '-'){ //if entered number is negative
        return 0;
    }
    return number;   //return the integer converted value
}
