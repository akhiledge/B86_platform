/**
 * @brief Function definition to create new node
 * @param word is a pointer storing base address of string
 * @param i_file is a pointer storing file name string
 * @return Created node address
 * */
hash *create_node(char *word, char *i_file)
{
    hash *new = malloc( sizeof(hash) );  ///Allocating memory for node

    assert(new);

    strcpy(new -> word, word);     ///Copying word to the created node

    new -> file_count = MAX;        ///File count
    new -> next = NULL;

    ///Function call to create count node
    new -> down = create_count(i_file);

    return new;
}

/**
 * @brief Function definition to create count node
 * @brief Stores file name for any word and word count in that file
 * */
detail *create_count(char *i_file)
{
    detail *new = malloc( sizeof(detail) );

    assert(new); 

    strcpy(new -> file_name, i_file);  ///Copying file name to the created node

    new -> word_count = MAX;            ///Initialising word count as one
    new -> down = NULL;

    return new;
}
