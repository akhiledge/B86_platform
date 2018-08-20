/*
*Function to copy hash table content to file*/
void copy_file(FILE *fptr, int argc) 
{ 
	NODE *temp = NULL;						 /*!<struct node ptr for traversing*/
	int i = 0;								/*!<index*/
	int count = 0;
	int j = 0;

	fprintf(fptr,"--------------------------------------\n");
	fprintf(fptr, "\tWords\t|\tfilename\t|Count\n");
    for(i = 0; i< SIZE; i++){										///loop from 0-SIZE					
       if(hashtable[i] != NULL){									///if value in hashtable is NULL, no entry
			fprintf(fptr, "Words starting from '%c'\n", *(hashtable[i]->data));
			fprintf(fptr,"--------------------------------------\n");
			temp = hashtable[i]; 
			 while(temp!= NULL){									///traversing linked list
				for(j = 0; j < (argc - 2) && temp->count[j]; j++){					///for multiple files
				fprintf(fptr,"%10s\t|", temp->data);
				fprintf(fptr, "%10s\t\t|\t%d\n",temp->filename[j],temp->count[j]);
				fprintf(fptr,"--------------------------------------\n");
				count += temp->count[j];
				}
				temp = temp->next;
			}
			fprintf(fptr, "Total count -\t\t\t\t\t%d\n", count);
			fprintf(fptr,"--------------------------------------\n\n\n");
		}
		count = 0;									///count re initialized to 0	 
     }
	fclose(fptr);									///closing new file 
}

