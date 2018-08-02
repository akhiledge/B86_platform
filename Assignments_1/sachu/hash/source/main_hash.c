/**
 * @author Sachu George
 * @date 24/07/2018
 * @brief Hash table implementation.
 * @Operations are create, display search, save and update database
 * */
int main(int argc, char *argv[])
{
    int option;
    int iter = MAX;
    FILE *i_fptr;             /*i_fptr is a file pointer */
    char word[SIZE];          /*! word is a string storing word scanned */
    char b_file[SIZE];        /*! b_file is a string storing file name */
    char temp[SIZE];          /*! temp is a string */
    char loop;
    hash *table[26] = {NULL}; /*! table is an array of pointer of size 26 */

    if(argc < 2)
    {
        fprintf(stderr, "Usage format : %s <input_text_files> or <backup_text_file>\n", argv[0]);
        exit(1);
    }

    do
    {
        ///Prompt for input from user
        printf("Choose any operation\n");
        printf("1.Create Database\n2.Display Data base\n");
        printf("3.Search\n4.Save Data base\n5.Update Data base\n");

        fgets(temp, SIZE, stdin);
        __fpurge(stdin);

        option = my_atoi(temp);

        switch (option)
        {
            case 1:
                while(iter < argc)
                {
                    i_fptr = fopen(argv[iter], "r");

                    if(i_fptr == NULL)
                    {
                        printf("No data found\n");
                        break;
                    }

                    while(fscanf(i_fptr, "%s", word ) > MIN)
                    {
                       modify_string(word);
                        
                        ///Function call for create database
                        create_database(argv[iter],table,word);
                    }
                    fclose(i_fptr);
                    iter++;
                }
                break;

            case 2:
                for(iter = MIN; iter < 26; iter++)
                {
                    //Function call for display database
                    print_list((table + iter));
                }
                break;

            case 3:
                printf("Enter the word to be searched\n");
                fgets(word, SIZE, stdin);

                modify_string(word);

                //Function call for search
                search_database(table, word);
                break;

            case 4:
                printf("Enter the file name to save data base\n");
                fgets(b_file, SIZE, stdin);


                //Function call for save database
                save_database(table, b_file);
                break;

            case 5:
                //Function call for update database
                update_database(argv[MAX], table);
                break;

            default:
                printf("Enter a valid option\n");
                break;

        }
        __fpurge(stdin);

        printf("Do you want to continue[y/n]\n");
        loop = getchar();
        __fpurge(stdin);
    }while(loop == 'y');

    return 0;
}
