/**
 * @brief Function definition to save database
 * @brief Function stores data into backup file
 * @param table is a pointer storing base address of hash table
 * @param b_file is a character pointer storing base address of backup file
 * */
void save_database(hash **table, char *b_file)
{
    FILE *b_ptr;
    int iter;
    hash *ptr;

    ///Opening backup file
    b_ptr = fopen(b_file, "w");

    //Calling function save_data for all hash table entries
    for(iter = MIN; iter < 26; iter++)
    {
        ptr = *(table + iter);

        if(ptr != NULL)
            save_data(&ptr, b_ptr);  
        else
            continue;
    }

    fclose(b_ptr);
}

///Function definition for saving data
void save_data(hash **head, FILE *b_ptr)
{
    hash *ptr = *head;
    detail *ptr1;

    ///Saving word, file_count, file_names, word_count into backup file
    while(ptr != NULL)
    {
        ptr1 = ptr -> down;
        fprintf(b_ptr, "%s", ptr -> word);

        putc(':', b_ptr);
        fprintf(b_ptr, "%d", ptr -> file_count);

        while(ptr1 != NULL)
        {
            putc(':', b_ptr);
            fprintf(b_ptr, "%s", ptr1 -> file_name);

            putc(':', b_ptr);
            fprintf(b_ptr, "%d", ptr1 -> word_count);

            ptr1 = ptr1 -> down;
        }

        putc('\n', b_ptr);
        ptr = ptr -> next;
    }
}
