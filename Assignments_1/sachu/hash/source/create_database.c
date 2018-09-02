/**
 * File              : create_database.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Function definition for creating node
 * \param i_file is a pointer storing base address of file name string
 * \param table is a pointer storing hash table base address
 * \param temp is a pointer storing base address of string
 * */
void create_database(char *i_file, hash **table, char *temp)
{
    int key;
    int ret;

    key = hash_index(temp[MIN]);       /* Function call to find
					  index value */
    if (key == INVALID) {               /* Invalid case */
	return;
    }
    if (table[key] == NULL) {           /*Checking hash table index */
	insert_first(&table[key], temp, i_file);   /*Index not filled
						     case */
    } else {
	ret = search_word(&table[key], temp);   /*Index filled case
						  -Checking for
						  repetition */
	if (ret == 0) {                     /* No repetition case */
	    insert_sorted(table, key, temp, i_file);
	} else {                           /* Repetition case */
	    update_count(&table[key], temp, i_file); /*Function call to
						       update count */
	}
    }
}
