
/**
 * File              : hanoi.c
 * Author            : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 * Date              : 29.08.2018
 * Last Modified Date: 31.08.2018
 * Last Modified By  : Vepuri Vinay Kumar <vk.vepuri@globaledgesoft.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE 16 /**< size of input buffer*/ 

/**
 *\brief move disks from source tower to destination tower
 *\param disk number of disk
 *\param src source tower
 *\param dest destination tower
 *\param aux auxilary tower
 **/ 
bool
tower_of_hanoi(unsigned int disk, char src, char dest, char aux)
{
	if (disk == 1) {
		printf("disk 1 moves from %c to %c\n", src, dest);
	} else {
		tower_of_hanoi(disk - 1, src, aux, dest);
		printf("disk %d moves from %c to %c\n", disk, src, dest);
		tower_of_hanoi(disk - 1, aux, dest, src);
	}
	return true;
}

int
main(void)
{
	int     no_of_disks = 0;
	char   *input_str = NULL;

	input_str = (char *)calloc(1, sizeof(char) * BUF_SIZE);
	while (no_of_disks < 1) {
		fputs("Enter the number of disks(greater than 0)\n", stdout);
		no_of_disks = atoi(fgets(input_str, BUF_SIZE, stdin));
	}
	tower_of_hanoi(no_of_disks, 'A', 'B', 'C');
    free(input_str);
    input_str = NULL;
	return 0;
}
