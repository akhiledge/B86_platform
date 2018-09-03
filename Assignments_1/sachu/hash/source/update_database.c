
/**
 * File              : update_database.c
 * Author            : Sachu George <g.sachu@globaledgesoft.com>
 * Date              : 26.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Sachu George <g.sachu@globaledgesoft.com>
 */

/**
 * \brief Function declaration to update database
 * */
void update_database(char *b_file, hash **table)
{
    FILE *b_ptr;
    char temp[100];
    char *token;
    char word[SIZE];
    char file_name[SIZE];
    int iter;
    int loop;
    int word_count;
    int file_count;

    b_ptr = fopen(b_file, "r");     /* Opening backup file */

    if (b_ptr == NULL) {
	printf("No data found\n");
	exit(1);
    }

    while (!feof(b_ptr)) {      /* Fetching data from file and updating
				   database */
	if (fscanf(b_ptr, "%s", temp) > 0) {
	    token = strtok(temp, ":");

	    strcpy(word, token);        /* Copying word */
	    if (token != NULL) {
		token = strtok(NULL, ":");

		file_count = my_atoi(token);    /* Finding file_count */

		for (iter = MIN; iter < file_count; iter++) {
		    token = strtok(NULL, ":");

		    strcpy(file_name, token);   /* Copying file_name */
		    token = strtok(NULL, ":");

		    word_count = my_atoi(token); /* Finding word_count */

		    /* Calling create data base function word_
		     * count times */
		    for (loop = MIN; loop < word_count; loop++) {
			create_database(file_name, table, word);
		    }
		}
	    }
	}
    }
    printf("Updating from backup file completed successfully\n");
    fclose(b_ptr);
}
