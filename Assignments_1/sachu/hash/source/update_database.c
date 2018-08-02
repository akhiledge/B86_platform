//Function declaration to update database
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

    ///Opening backup file
    b_ptr = fopen(b_file, "r");

    if(b_ptr == NULL)
    {
        printf("No data found\n");
        exit(1);
    }

    ///Fetching data from file and updating database
    while(!feof(b_ptr))
    {
        if(fscanf(b_ptr, "%s", temp) > 0)
        {
            token = strtok(temp, ":");

            ///Copying word
            strcpy(word, token);

            if(token != NULL)
            {
                token = strtok(NULL, ":");

                ///Finding file_count
                file_count = my_atoi(token);

                for(iter = MIN; iter < file_count; iter++)
                {
                    token = strtok(NULL, ":");

                    ///Copying file_name
                    strcpy(file_name, token);
                    token = strtok(NULL, ":");

                    ///Finding word_count
                    word_count = my_atoi(token);

                    ///Calling create data base function word_count times
                    for(loop = MIN; loop < word_count; loop++)
                    {
                        create_database(file_name, table, word);
                    }
                }
            }
        }
    }
    printf("Updating from backup file completed successfully\n");
    fclose(b_ptr);
}
