
/*
 * File:insert.c
 * Author:shrishail satihal
 * Description:inserting the words in to hashtable
 * Date:20-7-18
 * last modified:23-8-18
 * last modified by:shrishail satihal <s.shrishail@globaledgesoft.com>
 */

struct hashtable *root;
struct hashtable *prev;
struct hashtable *newnode;
void insert_node(char *str,
	char *file,
	int argc) /* function definition for insert operation which takes
		     an arguments string of type char file of type char and
		     argument count of type integer returns void */
{
    int index = get_index(*str); /* get index for particular string */

    if (hasharray[index] == NULL) { /* if index is NULL */
	newnode = create_node(str); /* create a node */
	hasharray[index] = newnode; /* store address of newnode into hasharray */
	(newnode->count[0])++; /* increment the node */
	strcpy(newnode->fname[0], file);
	return;
    } else {
	root = hasharray[index];
	prev = root;
	while (root != NULL) {
	    if (mystrcasecmp(str, root->str) == 0) { /* if the root string and
							next string both are
							same then increase
							the count */
		for (index = 0; index < (argc - 2); index++) {
		    if (strcmp(root->fname[index], file) == 0)
			(root->count[0])++;
		    else {
			strcpy(root->fname[index+1], file);
			(root->count[index+1])++;
		    }
		    return;
		}
	    }

	    if (mystrcasecmp(str, root->str) == -1) {
		newnode = create_node(str); /* create a newnode */
		strcpy(newnode->fname[0], file);
		if (root == hasharray[index]) {
		    hasharray[index] = newnode; /* store newnode address
						   into hash array*/
		    newnode->next = root;
		    (newnode->count[0])++; /*increment count */
		} else {
		    newnode->next = prev->next;
		    prev->next = newnode;
		    (newnode->count[0])++;
		}
		return;
	    }
	    prev = root;
	    root = root->next;
	}
	if (root == NULL) {
	    newnode = create_node(str);
	    strcpy(newnode->fname[0], file);
	    newnode->next = prev->next;
	    prev->next = newnode;
	    (newnode->count[0])++;
	}
    }
} /* end of inserting node function */


int mystrcasecmp(char *str1,
	char *str2)/* function definition for strcasecmp which takes argument
		      string1 and string2 and returns integer*/
{
    int i; /* i is an index which is of type integer */

    for (i = 0; str1[i] | str2[i]; i++) {
	/* check the case if it is capital make small */
	if (str1[i] >= 'A' && str1[i] <= 'Z')
	    str1[i] += 32;
	/* similarly for second string make it small case */
	if (str2[i] >= 'A' && str2[i] <= 'Z')
	    str2[i] += 32;
	if (str1[i] > str2[i])
	    /* return 1 if str1 greater */
	    return 1;
	if (str1[i] < str2[i])
	    /* if str2 greater return -1 else 0 */
	    return -1;
    }
    return 0;
} /* end of a mystrcasecmp function */

