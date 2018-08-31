/**
 * File              : value_in_node.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 31.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */

char   *input_str;

int
value_in_node(void)
{
	int     value;

	while (NULL == (input_str = allocate_memory(BUF_SIZE)));
	value = atoi(fgets(input_str, BUF_SIZE, stdin));
	free(input_str);
	input_str = NULL;
	return value;
}
