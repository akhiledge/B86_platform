/**
 * @brief Function to convert ascii to integer value
 * @param str is a string
 * @return Returns integer value on success and -1 on error
 * */
int my_atoi(char *str)
{
    int temp = MIN;
    int value;

    ///Looping till null character
    while((*str != '\0') && (*str != '\n'))
    {
        ///Checking for positive integer values
        if(((*str) < 48) || ((*str) > 57))
        {
            printf("Invalid input value\n");
            return INVALID;
        }

        value= *str - 48;
        temp = (temp * 10) + value;
        str++;
    }
    return temp;
}
