/**
 * File              : allocate_memory.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */

/****
 *@brief dynamic allocation of memory with validation
 *@param size number of bytes required
 * ****/
void   *
allocate_memory(size_t size)
{
	void   *alloc_ptr = NULL;

	alloc_ptr = calloc(1, size);
	if (alloc_ptr == NULL) {
		perror("Memory allocation failed\n");
	}
	return alloc_ptr;
}
