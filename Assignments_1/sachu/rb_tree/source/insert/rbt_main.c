/**
 * @author Sachu George
 * @date 13/07/2018
 * @brief Red Black tree operations
 * @Operations are insert delete and display
 * **/

#include <stdio.h>
int main()
{
    int option;  /*! option is integer to accept user input */
    int value;   /*! value to store integer element */
    char loop;   /*! loop to control looping */
    char input[SIZE];
    bst_t *root = NULL;  /*! Root of tree of type bst_t */

    do
    {
        ///Prompt for user input
        printf("Enter your choice\n");
        printf("1.insert_element\n2.Delete_element\n3.Display\n");

        fgets(input, SIZE, stdin);
        option = atoi(input);
        __fpurge(stdin);

        switch(option)
        {
            case 1:
                printf("Enter the element to be added\n");
                fgets(input, SIZE, stdin);
                value = atoi(input);
                insert_element(&root, value); ///Function call for inserting element
                break;

            case 2:
                root = delete_element(root);    ///Function call to delete a node
                break;

            case 3:
                display_tree(root);          ///Function call to display tree
                break;
                
            default:
                printf("Invalid input\n");
                break;
        }

        printf("Do you want to continue[y/n]\n");
        loop = getchar();
        __fpurge(stdin);

    }while(loop == 'y');
    return 0;
}
