/**
 * @brief Function for philosopher
 * @param value is void pointer
 * */
void *philosopher_fun(void *value)
{
    while(1)
    {
        int *iter = (int *) value;

        fork_acquire(*iter); ///Function call for acquiring fork
        fork_release(*iter); ///Function call for releasing fork
    }
}
