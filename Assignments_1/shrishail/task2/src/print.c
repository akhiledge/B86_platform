
/*
 * File:print.c
 * Author:shrishail satihal
 * Description:copying the contents into another file
 * Date:20-7-18
 * last modified:23-8-18
 * last modified by:shrishail satihal <s.shrishail@globaledgesoft.com>
 */

void copy_file(FILE *fp2,
	int argc) /*Function definition for copying contents into file
		    which takes aguments file pointer and argument count which
		    returns void */
{
    struct hashtable *temp = NULL;
    int index = 0;
    int j_index = 0;
    int count = 0;

    fprintf(fp2, "\twords\t|filename\t|count\n");
    for (index = 0; index < SIZE; index++) { /*iterate till the end of
					     indexex in hash table */
	if (hasharray[index] != NULL) {
	    fprintf(fp2, "string starting from %c\n", *(hasharray[index]->str));
	    temp = hasharray[index];
	    while (temp != NULL) {
		for (j_index = 0; j_index < (argc-2) \
			&& temp->count[j_index]; j_index++) {

		    fprintf(fp2, "str:=%-20s file:= %-10s count:=%-10d\n" \
			    , temp->str, temp->fname[j_index], \
			    temp->count[j_index]);

		    count = count + temp->count[j_index];
		}
		temp = temp->next; /* traverse till the end of list */
	    }
	    fprintf(fp2, "total:%-10d\n", count);
	}
	count = 0;
    }
    fclose(fp2);
}
