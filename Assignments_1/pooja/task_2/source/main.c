/**
* @author Poojashree M
 *@brief: Reading a file and placing the contents in the hash file
*@operation Interface to choose insert to hash table, copy hash table content to file, Search a string, Exit
*@param source files and destination file as command line arguments
 *@date: 23/07/2018
 */

NODE *hashtable[ARR_SIZE] = {NULL};

int main(int argc, char **argv)
{
	FILE *fptr1 = NULL;					/*!<ptr to FILE structure*/
	FILE *fptr2 = NULL;					/*!<ptr to FILE structure*/
	char *str = NULL;					/*!<character ptr for fgets*/
	char *word = NULL;					/*!<character ptr for reading from file*/
	int choice = 0;						/*!<int variable for choice*/
	int i = 0;
	int ret_value = 0;					/*!<int variable for return from search*/	char str_search[SIZE]; 

	str = (char *) malloc(SIZE);
	assert(str);						///Malloc validation for str

	word = (char *) malloc(SIZE);
	assert(word);						///Malloc validation for word

//	str_search = (char *) malloc(SIZE);
//	assert(str_search);	
				
	if(argc < 3){										///validation of command line arguments
		printf("Format : %s <file name1> <file name2>\n", argv[0]);
		return 0;
	}

	system("clear");
	printf("--------------------------------------------------------------------*****----------------------------------------------------------------------\n");
	while(1){
		printf("Enter choice\n");									///Input from user
		printf("1. Insert file contents to hash table\n");			///options availbale
		printf("2. Copy hash table to new file\n");
		printf("3. Search the string\n");
		printf("4. Exit\n");
		printf("___________________________________________\n");
		printf("choice :");
		__fpurge(stdin);
		fgets(str, sizeof(int), stdin);
		assert(str);												///fgets validation

		choice = atoi(str);											///atoi conversion of str
		switch(choice){
			case 1: for(i = 1; i < (argc -1); i++){					///opening multiple files depending on CLA
						fptr1 = fopen(argv[i], "r");				///opening file in read mode
						if(fptr1 == NULL){							///fopen validation
							perror("File cannot be opened\n");
							return 0;
						}

						while((fscanf(fptr1, "%s", word)) != EOF){	///read each word from file
							insert(word, argv[i], argc);						///function call
						}
						fclose(fptr1);
						printf("%c) file %s contents are placed to hash table\n", 96+i, argv[i]); 
					}
					
					printf("___________________________________________\n");
					break;

			case 2: fptr2 = fopen(argv[argc-1], "w");
					if(fptr2 == NULL){							///fopen validation
						perror("File cannot be opened\n");
						return 0;
					}		
					copy_file(fptr2, argc);							///function call
					printf("Hash table contents are copied to %s file\n", argv[argc-1]);
					printf("___________________________________________\n");
					break;

			case 3: printf("Enter the data to be searched in hash table\n");	
					__fpurge(stdin);
					fgets(str_search, SIZE, stdin);						///user input
					modify(str_search);									///to remove '\n'
					ret_value = search(str_search);						///search function call
					if(ret_value == -1)
					printf("String not found\n");		
					printf("___________________________________________\n");
					break;
							
			case 4: printf("Exiting ...\n");
					printf("--------------------------------------------------------------------*****----------------------------------------------------------------------\n");
					return 0;///exit

			default:printf("Invalid option\n");
					printf("Exiting ...\n");
					printf("--------------------------------------------------------------------*****----------------------------------------------------------------------\n");
		}
	}
	return 0;
}
