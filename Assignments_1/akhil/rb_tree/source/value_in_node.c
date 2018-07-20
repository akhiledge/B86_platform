char *input_str;
int value_in_node (void){
    int value; 
    while (NULL == (input_str = allocate_memory (BUF_SIZE)));
    value = atoi (fgets (input_str, BUF_SIZE, stdin));
    free (input_str);
    input_str = NULL;
    return value;
}
