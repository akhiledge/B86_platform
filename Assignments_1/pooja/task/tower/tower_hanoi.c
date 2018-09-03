
/**
 * File              : tower_hanoi.c
 * Author            : Poojashree M <m.poojashreeglobaledgesoft.com>
 * Date              : 16.07.2018
 * Brief			 : Tower of hanoi solution using recursive function
 * Last Modified Date: 02.09.2018
 * Last Modified By  : Poojashree M <m.poojashreeglobaledgesoft.com>
 */

/**Header files inclusion*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX 10 /*!@def : Macro MAX for string size*/

/**Function declaration*/
void tower(int num, char from_rod, char to_rod, char aux_rod);

/**@brief: main function used to get input and invokes tower function
 *@param: No arguments
 *@return: Returns 0 on success
 */
int main(void)
{
	char *str = NULL;
	char from_rod = 'A'; /*!<@var : from rod*/
	char aux_rod = 'B'; /*!<@var: auxillary rod*/
	char to_rod = 'C'; /*!<@var : destination rod*/
	char num = 0; /*!<@var : Number of disks*/

	str = (char *) malloc(sizeof(MAX));
	assert(str); /**Malloc validation*/

	printf("Enter the number of disks\n");
	str = fgets(str, sizeof(int), stdin);
	assert(str); /**fgets validation*/

	num = atoi(str); /**atoi conversion*/
	tower(num, from_rod, to_rod, aux_rod); /**Function call*/
	return 0;
} /**End of main*/

/**@brief: Function definition for tower
 *@param: Number of disks(num) of type int, from rod(from_rod),
 *			auxillary rod(aux_rod) and destination rod(to_rod) of type char
 *@return: void
 */
void tower(int num, char from_rod, char aux_rod, char to_rod)
{
	if (num == 1) {
		printf("Disk %d moved from %c to %c\n", num, from_rod, aux_rod);
		return;
	}
	tower(num - 1, from_rod, to_rod, aux_rod); /**recursive function
												 call with decremented disk*/
	printf("Disk %d moved from %c to %c\n", num, from_rod, aux_rod);
	tower(num - 1, to_rod, aux_rod, from_rod); /**recursive function
												 call*/
} /**End of tower function definition*/
