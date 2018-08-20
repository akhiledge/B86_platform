/**To display the hash table contents in the std output*/

void display()
{
	struct node *temp = NULL;
	int i = 0;
	printf("IN DISPLAY\n");
	for(i = 0; i< SIZE; i++){
		if(hashtable[i] != NULL){
			temp = hashtable[i];
			while(temp!= NULL){
			printf("%s\n", temp->data);
			printf("count-%d\n", temp->count[0]);
			temp = temp->next;
		}
	}
	}
}
