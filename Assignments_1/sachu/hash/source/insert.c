
/**
 * File              : insert.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 24.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */
/**
 * \brief Function definition for insert operation.
 * Operations insert_first, insert last, insert before
 * \param table is a pointer storing hash table base address
 * \param key is a integer storing hash table index
 * \param temp is a pointer storing base address of string
 * \param i_file is a pointer storing base address of file name string
 * */

void insert_sorted(hash **table, int key, char *temp, char *i_file)
{
    hash *ptr = table[key];

    while ((strcmp(ptr->word, temp) <= MIN)
            && ptr->next != NULL) { /* Incrementing pointer till first
                                       large word or till last */
        ptr = ptr->next;
    }
    if ((strcmp(ptr->word, temp) > MIN)) {   /* Inserting before case */
        insert_before(&table[key], temp, i_file);
    } else {                        /* Insert as last */
        insert_last(&table[key], temp, i_file);
    }
}

/**
 * \brief Function definition for insert first
 * */
void insert_first(hash **head, char *word, char *i_file)
{
    *head = create_node(word, i_file);
}


/**
 * \brief Function definition for insert last
 * */
void insert_last(hash **head, char *word, char *i_file)
{
    hash *ptr = *head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = create_node(word, i_file);      /* Calling create node 
                                                   function */
}

/**
 * \brief Function definition for insert before
 * */
void insert_before(hash **head, char *word, char *i_file)
{
    hash *ptr = *head;
    hash *ptr1 = ptr;

    while (ptr != NULL) {
        if (strcmp(ptr->word, word) > MIN) {
            hash *new = create_node(word, i_file);  /* Calling create 
                                                       node function */

            /* /Arranging addresses */
            (ptr == *head) ? (new->next = *head) : (
                    new->next = ptr1->next);
            (ptr == *head) ? (*head = new):(ptr1->next = new);
            return;
        }
        ptr1 = ptr;
        ptr = ptr->next;             /* Incrementing pointers */
    }
}
