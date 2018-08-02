/**
 * @brief Function definition to remove \n character
 * @param str is a character pointer storing base address of string
 * */
void modify_string(char *str)
{
    int len = strlen(str) - 1;  //To check for ',' or '.' or '\n' character

    if((str[len] == '.') || (str[len] == ',') || (str[len] == '\n'))
    {
        while((*str != '\n') && (*str != '\0') && (*str != ',') && (*str != '.'))
            str++;
        *str = '\0';
    }
}
