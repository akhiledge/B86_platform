
/*
 * File:create.c
 * Author:shrishail satihal
 * Description:creating a node to insert into hash table
 * Date:20-7-18
 * last modified:23-8-18
 * last modified by:shrishail satihal <s.shrishail@globaledgesoft.com>
 */

struct hashtable *create_node(char *str) /*function definition for creating
					   a node which takes string as a
					   argument and returns pointer to
					   a structure*/
{
    struct hashtable *newnode;
    /* allocating a memory for newnode  */
    newnode  = (struct hashtable *)malloc(sizeof(struct hashtable));
    if (newnode == NULL) { /*malloc validation*/
	printf("malloc failed\n");
	exit(0);
    }
    newnode->str = (char *)malloc(sizeof(char)*MAX);
    strcpy(newnode->str, str); /*copying string*/
    assert(newnode);
    memset(newnode->count, 0, MAX);
    newnode->next = NULL;
    return newnode;
} /*end of creating node function*/


