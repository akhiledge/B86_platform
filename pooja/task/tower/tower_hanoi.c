/**TOWER OF HANOI */
///@author Poojashree M
///@date 16/07/18
///Header files inclusion
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define MAX 10				///Macro for string size

///Function declaration
void tower(int num, char from_rod, char to_rod, char aux_rod);

int main()
{
	char *str = NULL;
	char from_rod = 'A';					/*!<from rod*/	
	char aux_rod = 'B';
	char to_rod = 'C';
	char num = 0;							///Variable for Number of disks

	str = (char *) malloc(sizeof(MAX));
	assert(str);							///Malloc validation

	printf("Enter the number of disks\n");
	str = fgets(str, sizeof(int), stdin);
	assert(str);							///fgets validation

	num = atoi(str);						///atoi conversion

	tower(num, from_rod, to_rod, aux_rod);	///Function call 

	return 0;
}

///Function definition for tower
void tower(int num, char from_rod, char aux_rod, char to_rod)
{
		if(num == 1){
			printf("Disk %d moved from %c to %c\n", num, from_rod, aux_rod);
			return;
		}
		
		tower(num - 1, from_rod, to_rod, aux_rod);						///recursive function call with decremented disk
		printf("Disk %d moved from %c to %c\n", num, from_rod, aux_rod);
		tower(num - 1, to_rod, aux_rod, from_rod);
}
