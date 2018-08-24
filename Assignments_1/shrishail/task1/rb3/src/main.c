/*
 * File:main.c
 * Author:shrishail Satihal
 * Date:23-8-18
 * Last modified:23-8-18
 * Description:RB tree insertion
 */

int main(void)                                                                      
{                                                                               
    char *str = NULL;                                                           
    rbtree *root = NULL;                 
    str = (char *) malloc(MAX);
    assert(str);
    int option;
    int val;              
    while (1) {
        printf("Enter choice\n");                                               
        printf("1.insert node into tree\n2.display the nodes\n3.exit\n");                        
        fgets(str, MAX, stdin);                                                 
        assert(str);                                                            
        option = atoi(str);                             
        switch (option) {
            case 1: printf("input a number\n");                 
                    fgets(str, MAX, stdin);                                     
                    val = atoi(str);                                           
                    root = insert(root, val);                             
                    break;                                                      
            case 2: print(root);                              
                    break;                                                      
            case 3: exit(0);                                                    
            default: printf("Invalid argument! check again\n");                                
        }                                                                       
    }        
    free(str);
    str=NULL;
    return 0;    
}                                                                               

