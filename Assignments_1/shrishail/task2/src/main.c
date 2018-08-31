/*
 * File:main.c
 * Author:shrishail satihal
 * Description:Hash table implementation for counting words occurence
 * Date:23-8-18
 * last modified:23-8-18
 * last modified by:shrishail satihal <s.shrishail@globaledgesoft.com>
 */

int main(int argc,char *argv[])
{
    char *str = (char *)malloc(sizeof(char) * MAX);
    if (str == NULL) { ///validation for malloc
        printf("malloc failed\n");
        exit(0);
    }
    char *str1 = (char *)malloc(sizeof(char) * MAX);
    if (str1 == NULL) { ///validation for malloc 
        printf("malloc failed\n");
        exit(0);
    }
    FILE *fp1; ///fp1 is file pointer to a structure FILE
    FILE *fp2; ///fp2 is file pointer to a structure FILE
    int choice;
    int index;
    while (1) {
        printf("enter the choice:\n");
        printf("1.insert in to hash table\n");
        printf("2.copy\n");
        printf("3.display\n");
        printf("4.exit\n");
        fgets(str, MAX, stdin);
        choice = atoi(str);
        switch (choice) {
            case 1:for (index=1; index < (argc-1); index++) {
                       fp1 = fopen(argv[index],"r");///file opening in readmode
                       if (fp1 == NULL) { ///validation for fopen
                           printf("unable to open afile\n");
                           exit(0);
                       }
                       printf("hash table created\n");
                       while ((fscanf(fp1, "%s", str1)) != EOF) { ///reading\
                           each words from file
                               insert_node(str1, argv[index], argc);
                       }
                       fclose(fp1); ///closing a file
                   }
                   break;

            case 2:fp2 = fopen(argv[argc-1], "w"); ///opening file in writemode
                   if (fp2 == NULL) { ///validation for fopen
                       printf("unable to open a file\n");
                       exit(0);
                   }
                   printf("copy into another file\n");
                   copy_file(fp2, argc);///function call for copying the \
                   contents into file
                   break;

            case 3:fp2 = fopen(argc[argv-1], "w");
                   if (fp2 == NULL) {
                       printf("unable to open a file\n");
                       exit(0);
                   }
                   display(fp2, argc); ///funtcion call for displaying content
                   break;

            case 4:exit(0);
                   break;

            default:printf("invalid option\n");

        }   
    }
    free(str);
    free(str1);
    str = str1 = NULL;
    return 0;
}					      	 

