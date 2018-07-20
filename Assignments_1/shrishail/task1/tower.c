/**
*@headerfile stdio.h
*/
#include<stdio.h>
/**
*@headerfile stdlib.h
*/
#include<stdlib.h>
/**
* @def MAX
*/
#define MAX 50
//function prototype for tower of honoi
void tower_of_honoi(int, char, char, char);
int main(void)
{
		int disk; /*!@disk disk is a integer variable*/
		char *str=(char *)malloc(sizeof(char)*MAX);
		printf("enter the number of disks\n");
		fgets(str,MAX,stdin);
		disk=atoi(str);
		//function call for tower of honoi to send disks from source to destination
		tower_of_honoi(disk,'A','C','B');
		return 0;
}
void tower_of_honoi(int disk1,char src1,char dest1,char aux1)
{
		//if disk is only one move disk from source to destination
		if(disk1==1)
		{
				printf("disk 1 moves from %c to %c\n",src1,dest1);
				return;
		}
		else
		{
				//recursive call for disks to move from source to auxilary rod
				tower_of_honoi(disk1-1,src1,aux1,dest1);
				printf("disk %d  moves from %c to %c\n",disk1,src1,dest1);
				//recursive call for disks to move from auxilary to destination rod
				tower_of_honoi(disk1-1,aux1,dest1,src1);
		}
}
