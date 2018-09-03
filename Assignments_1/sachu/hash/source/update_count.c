
/**
 * File              : update_count.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 25.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to update count-Word repetition case
 * \param head is a pointer storing hash table index address
 * \param temp is a pointer storing base address of string
 * \param i_file is a pointer storing base address of file name string
 * */
void update_count(hash **head, char *temp, char *i_file)
{
    hash *ptr = *head;

    while (ptr != NULL) {
	if (strcmp(ptr->word, temp) == MIN) {
	    detail *ptr1 = ptr->down;

	    while ((ptr1->down != NULL) || (strcmp(ptr1->file_name,
			    i_file) == MIN)) {  /* Checking whether
						   new file_name */

		if (strcmp(ptr1->file_name,
			    i_file) == MIN) {      /* Repeatition in same
						      file case */
		    ptr1->word_count++;         /* Incrementing
						   word_count */
		    return;
		} else {
		    ptr1 = ptr1->down;
		}
	    }
	    /* New file case */
	    ptr1->down = create_count(i_file);
	    ptr->file_count++;      /* Incrementing file_count */
	    return;
	}
	ptr = ptr->next;
    }

}
