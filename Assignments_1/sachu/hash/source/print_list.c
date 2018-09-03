/**
 * File              : print_list.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 25.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function definition to display database
 * \param head is a pointer storing index address of hash table
 * */
void print_list(hash **head)
{
    if (*head == NULL) {         /* No name condition */
	return;
    }
    hash *ptr = *head;
    detail *ptr1;

    while (ptr != NULL) {
	ptr1 = ptr->down;
	printf("Word = %s\n", ptr->word);   /* Printing hash table
					       data */
	printf("File_count = %d\n", ptr->file_count);

	while (ptr1 != NULL) {
	    printf("File_name = %s\n", ptr1->file_name);
	    printf("Word_count = %d\n", ptr1->word_count);
	    ptr1 = ptr1->down;
	}
	printf("*****************************\n");
	ptr = ptr->next;
    }
}
