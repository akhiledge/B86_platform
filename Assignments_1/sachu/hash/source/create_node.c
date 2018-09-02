
/**
 * File              : create_node.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to create new node
 * \param word is a pointer storing base address of string
 * \param i_file is a pointer storing file name string
 * \return Created node address
 * */
hash *create_node(char *word, char *i_file)
{
    hash *new = malloc(sizeof(hash));  /* Allocating memory for node */

    assert(new);

    strcpy(new->word, word);
    new->file_count = MAX;
    new->next = NULL;

    new->down = create_count(i_file);   /* Function call to create
    count node */
    return new;
}

/**
 * \brief Function definition to create count node
 * \brief Stores file name for any word and word count in that file
 * */
detail *create_count(char *i_file)
{
    detail *new = malloc(sizeof(detail));

    assert(new);
    strcpy(new->file_name, i_file);
    new->word_count = MAX;
    new->down = NULL;

    return new;
}
