//void *alloc_ptr;
void *allocate_memory (int size){
    void *alloc_ptr = NULL;
    alloc_ptr = calloc (1, size);
    if (NULL == alloc_ptr){
        perror ("Memory allocation failed\n");
    }
    return alloc_ptr;
}
