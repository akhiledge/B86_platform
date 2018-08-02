/****
 *brief: dynamic allocation of memory with validation
 *@param size number of bytes required
 * ****/ 
void *allocate_memory (size_t size){
    void *alloc_ptr = NULL;
    alloc_ptr = calloc (1, size);
    if (NULL == alloc_ptr){
        perror ("Memory allocation failed\n");
    }
    return alloc_ptr;
}
