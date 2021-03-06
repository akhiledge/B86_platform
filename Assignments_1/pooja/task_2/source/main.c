/**
 * File              : main.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 23.07.2018
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**
*@brief: Reading a file and placing the contents in the hash file
*@operation Interface to choose insert to hash table, copy hash table
*content to file, Search a string, Exit
*@param source files and destination file as command line arguments
 */

NODE *hashtable[ARR_SIZE] = {NULL};		/*!<Array of pointers
										used for hash table entries*/

int main(int argc, char **argv)
{
	FILE *fptr1 = NULL;					/*!<ptr to FILE structure*/
	FILE *fptr2 = NULL;					/*!<ptr to FILE structure*/
	char *str = NULL;					/*!<character ptr for fgets*/
	char *word = NULL;					/*!<character ptr for reading
										  from file*/
	int choice = 0;						/*!<int variable for choice*/
	int i = 0;
	int ret_value = 0;					/*!<int variable for return
										  from search*/	
	char str_search[SIZE];				/*!<character array*/

	str = (char *) malloc(SIZE);
	assert(str);						/**Malloc validation for str*/

	word = (char *) malloc(SIZE);
	assert(word);						/**Malloc validation for word*/

				
	if (argc < 3) {						/**validation of command line
										arguments*/
		printf("Format : %s <file name1> <file name2>\n", argv[0]);
		return 0;
	}

	system("clear");
	printf("---------------------------------------------------------\
			-----------*****-----------------------------------------\
			-----------------------------\n");
	while (1) {
		printf("Enter choice\n");						/**Input from user*/
		printf("1. Insert file contents to hash table\n"); /**options 
															 availbale*/
		printf("2. Copy hash table to new file\n");
		printf("3. Search the string\n");
		printf("4. Exit\n");
		printf("___________________________________________\n");
		printf("choice :");
		__fpurge(stdin);
		fgets(str, sizeof(int), stdin);
		assert(str);									/**fgets validation*/

		choice = atoi(str);								/**atoi conversion
														of str*/
		switch (choice) {
		case INSERT: for (i = 1; i < (argc -1); i++) {	/**opening multiple
															  files depending
															  on CLA*/
						fptr1 = fopen(argv[i], "r");		/**opening file
															  in read mode*/
						if (fptr1 == NULL) {				/**fopen
															  validation*/
							perror("File cannot be opened\n");
							return 0;
						}

						while ((fscanf(fptr1, "%s", word)) != EOF) { /**read
														each word from file*/
							insert(word, argv[i], argc); /**function call*/
						}
						fclose(fptr1);
						printf("%c) file %s contents are placed to\
							hash table\n", 96+i, argv[i]); 
					}
					
					printf("___________________________________________\n");
					break;

		case COPY: fptr2 = fopen(argv[argc-1], "w");
					if(fptr2 == NULL){					/**fopen validation*/
						perror("File cannot be opened\n");
						return 0;
					}		
					copy_file(fptr2, argc);				/**copy_file function
														  call*/
					printf("Hash table contents are copied to\
							%s file\n", argv[argc-1]);
					printf("___________________________________________\n");
					break;

		case SEARCH: printf("Enter the data to be searched in hash table\n");	
					__fpurge(stdin);
					fgets(str_search, SIZE, stdin);		/**user input*/
					modify(str_search);					/**to remove '\n'*/
					ret_value = search(str_search);		/**search function
														  call*/
					if (ret_value == -1) {
						printf("String not found\n");
					}		
					printf("___________________________________________\n");
					break;
							
		case EXIT: printf("Exiting ...\n");
					printf("----------------------------------------------\
							----------------------*****-------------------\
							----------------------------------------------\
							-----\n");
					return 0;								/**exit*/

		default:printf("Invalid option\n");
				printf("Exiting ...\n");
				printf("--------------------------------------------\
							------------------------*****--------------\
							-------------------------------------------\
							-------------\n");
		}
	}
	return 0;
}
