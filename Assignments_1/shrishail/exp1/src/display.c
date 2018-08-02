//#include"header.h"
void display(FILE *fp2, int *argc)
{
	struct hashtable *temp=NULL;
	int index = 0;
	int j_index = 0;
	int count = 0;
	for(index = 0; index < SIZE; index++)///iterate till the end of indexex in hash table
	{
		if(hasharray[index] != NULL)
		{
			temp = hasharray[index];
			while(temp!=NULL){
				for(j_index = 0; j_index < (argc-2) && temp->count[j_index]; j_index++){
					printf("str:=%-15s file:= %-10s count:=%-7d\n",temp->str,temp->fname[j_index],temp->count[j_index]);
			//		fprintf(fp2,"str:=%s:=%d\n",temp->fname[j],temp->count[j]);
					count=count+temp->count[j_index];
				}
				temp=temp->next; ///traverse till the end of list
			}
//			printf("\n");
			printf("total:%-7d\n",count);
		}
	}
//	fclose(fp2);
}
