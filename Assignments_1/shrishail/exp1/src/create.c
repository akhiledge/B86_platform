//#include"header.h"
struct hashtable *create(char *str)
{
    struct hashtable *newnode = (struct hashtable *)malloc(sizeof(struct hashtable)); ///allocating memory for newnode 
    if(newnode == NULL)
    {
        printf("malloc failed\n");
        exit(0);
    }
    ///creating newnode to insert in to hash table
    newnode->str=(char *)malloc(sizeof(char)*MAX);
    strcpy(newnode->str,str); ///copying string 
    assert(newnode); 
    memset(newnode->count,0,MAX);
    newnode->next=NULL;
    return newnode;
}


