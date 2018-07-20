/******
 *main function for rb tree
 ******/ 
node *root = NULL;
int main (void) {

    int option = 0;
    int data = 0;
    bool (*function[])() = {insert, inorder, preorder, postorder};

    while (true){
        option = user_input();
        if ((option < 5) && (option > 1)){
            (function[option - 1])(root);
        }
        else {
            if (1 == option){
                fputs ("enter value: ", stdout);
                data = value_in_node ();
                if (function[option - 1](data)){
                    printf (" element %sted\n", (option == 1)?"inser":"dele"); 
                }
                else
                    printf ("%s found\n ", (option == 1)?"duplicate":"element not"); 
            }
            else if (5 == option){
                return 0;
            }
            else{
                fputs ("enter a valid option\n", stdout);
            }
        }
    }

    return 0;
}
