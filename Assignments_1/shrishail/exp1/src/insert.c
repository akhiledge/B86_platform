
//#include"header.h"
struct hashtable* root = NULL;
struct hashtable* prev = NULL;
struct hashtable* newnode = NULL;
void insert(char *str, char *dest, int argc)
{
    int index = get_index(*str); ///get index for particular string
    if(hasharray[index] == NULL) ///if index is NULL
    {
        newnode = create(str); ///create a node
        hasharray[index] = newnode; ///store address of newnode into hasharray
        (newnode->count[0])++; ///increment the node
        strcpy(newnode->fname[0], dest);
        return;
    }
    else
    {
        root = hasharray[index]; 
        prev = root;
        while(root != NULL){
            if(mystrcasecmp(str,root->str) == 0){ ///if root node and next string both are same then increase the count

                for(index=0; index < (argc -2); index++){

                    if(strcmp(root->fname[index],dest) == 0)
                        (root->count[0])++;
                    else{

                        strcpy(root->fname[index+1],dest);
                        (root->count[index+1])++;
                    }
                    return;
                }
            }



            if(mystrcasecmp(str,root->str) == -1){  ///if root string is greater than next string
                newnode = create(str); ///create a newnode
                strcpy(newnode->fname[0],dest);
                if(root == hasharray[index]){
                    hasharray[index] = newnode; ///store newnode address into hash array
                    newnode->next = root; 
                    (newnode->count[0])++; ///increment count 
                }
                else{
                    newnode->next = prev->next;
                    prev->next = newnode;
                    (newnode->count[0])++;
                }
                return;
            }
            prev = root;
            root = root->next;
        }
        if(root == NULL){
            newnode = create(str);
            strcpy(newnode->fname[0],dest);
            newnode->next = prev->next;
            prev->next = newnode;
            (newnode->count[0])++;
        }
    }
}


int mystrcasecmp(char *str1,char *str2)
{
    int i;
    for(i=0; str1[i]|str2[i]; i++){
        //check the case if it is capital make small
        if(str1[i] >= 'A' && str1[i] <='Z')
            str1[i]+=32;
        //similarly for second string make it small case
        if(str2[i] >= 'A' && str2[i] <='Z')
            str2[i]+=32;
        if(str1[i] > str2[i])
            //return 1 if str1 greater
            return 1;
        if(str1[i] < str2[i] )
            //if str2 greater return -1 else 0
            return -1;
    }
    return 0;
}

