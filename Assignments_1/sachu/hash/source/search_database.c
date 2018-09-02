
/**
 * File              : search_database.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 26.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition for searching word
 * \param table is a pointer storing hash table base address
 * \param word is a pointer storing base address of string
 * */
void search_database(hash **table, char *word)
{
    int key;
    int ret;

    key = hash_index(*word);     /* Function call to check index */

    if (key == INVALID) {       /* Invalid search input */
	printf("ERROR!Invalid search input\n");
	return;
    }

    if (table[key] == NULL) {     /* Case - List empty */
	printf("Word not found\n");
	return;
    } else {
	ret = search_word(&table[key], word);  /* Function call for
						  searching for word */

	if (ret == MIN) {       /* Case - Word not found */
	    printf("Word not found\n");
	    return;
	} else {
	    find_word(&table[key], word);  /* Function call to
					      find word count */
	}
    }
}

/**
 * \brief Function definition for searching word
 * */
int search_word(hash **head, char *name)
{
    hash *ptr = *head;

    while (ptr != NULL) {       /* Checking till last node */
	if (strcmp(ptr->word, name) == MIN) {
	    return MAX;         /* Word present case */
	}
	ptr = ptr->next;
    }
    return MIN;             /* Case - Word not found */
}

/**
 * \brief Function declaration to find word count
 * */
void find_word(hash **head, char *name)
{
    hash *ptr = *head;

    while (strcmp(name, ptr->word) != MIN) {
	ptr = ptr->next;
    }
    detail *ptr1 = ptr->down;

    /* Printing word and its count in all input files */
    printf("********************************\n");
    printf("String %s is present in %d file(s)\n", name,
	    ptr->file_count);

    while (ptr1 != NULL) {
	printf("In %s %d time(s)\n", ptr1->file_name,
		ptr1->word_count);
	ptr1 = ptr1->down;
    }

    printf("********************************\n");
}
