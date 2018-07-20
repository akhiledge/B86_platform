//char *input_str;
int user_input (void){
    char *input_str = NULL;
    int value;
    while (NULL == (input_str = allocate_memory (BUF_SIZE)));
    fputs("\nselect an option\n", stdout); 
    fputs ("1.Insert\n2.inorder display\n3.preorder display\n", stdout);
    fputs ("4.postorder display\n5.exit\n", stdout);
    value = atoi (fgets (input_str, BUF_SIZE, stdin));
    free (input_str);
    input_str = NULL;
    return value;
}
