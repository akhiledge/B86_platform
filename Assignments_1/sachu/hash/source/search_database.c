/**
 * @brief Function definition for searching word
 * @param table is a pointer storing hash table base address
 * @param word is a pointer storing base address of string
 * */
void search_database(hash **table, char *word)
{
    int key;
    int ret;

    key = hash_index(*word);     ///Function call to check index

    ///Invalid search input
    if(key == INVALID)
    {
        printf("ERROR!Invalid search input\n");
        return;
    }

    ///Case - List empty
    if(table[key] == NULL)
    {
        printf("Word not found\n");
        return;
    }

    else
    {
        ret = search_word(&table[key], word);  ///Function call for searching for word

        ///Case - Word not found
        if(ret == MIN)
        {
            printf("Word not found\n");
            return;
        }
        else
            find_word(&table[key], word);  ///Functionn call to find word count
    }
}

/**
 * @brief Function definition for searching word
 * */
int search_word(hash **head, char *name)
{
    hash *ptr = *head;

    ///Checking till last node
    while(ptr != NULL)
    {
        if(strcmp(ptr -> word, name) == MIN)
        {
            return MAX; ///Word present case
        }
        ptr = ptr -> next;
    }

    ///Case - Word not found
    return MIN;
}

/**
 * @brief Function declaration to find word count
 * */
void find_word(hash **head, char *name)
{
    hash *ptr = *head;
    while( strcmp(name, ptr -> word) != MIN)
    {
        ptr = ptr -> next;
    }
    detail *ptr1 = ptr -> down;

    //Printing word and its count in all input files
    printf("********************************\n");
    printf("String %s is present in %d file(s)\n", name, ptr -> file_count);

    while(ptr1 != NULL)
    {
        printf("In %s %d time(s)\n", ptr1 -> file_name, ptr1 -> word_count);
        ptr1 = ptr1 -> down;
    }

    printf("********************************\n");
}
