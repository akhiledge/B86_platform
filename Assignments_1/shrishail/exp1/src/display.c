
/*
 * File:display.c
 * Author:shrishail satihal
 * Description:displaying the contents
 * Date:23-8-18
 * last modified:23-8-18
 */
void display(FILE *fp2, 
        int argc)///function definition for display which takes\
         arguments file pointer and argument count and returns void
{
    struct hashtable *temp = NULL;
    int index = 0;
    int j_index = 0;
    int count = 0;
    for (index = 0; index < SIZE; index++) { ///iterate till the end of \
        indexex in hash table
        if (hasharray[index] != NULL) {
            temp = hasharray[index];
            while (temp != NULL) {
                for (j_index = 0; j_index < (argc-2) \
                        && temp->count[j_index]; j_index++) {
                    printf("str:= %-15s file:= %-10s count:=%-7d\n" \
                            , temp->str,temp->fname[j_index] \
                           , temp->count[j_index]);
                    count = count + temp->count[j_index];
                }
                temp = temp->next; ///traverse till the end of list
            }
            printf("total:%-7d\n", count);
        }
        count = 0;
    }
    fclose(fp2);
}///end of function displaying the contents 
