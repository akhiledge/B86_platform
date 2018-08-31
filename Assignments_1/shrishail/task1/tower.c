
/*
File:tower.c
Author:shrishail satihal
Description:Moving a disks from one tower to another tower
Date:23-8-18
Last modified:23-8-18
Last modified by:Shrishail Satihal <s.shrishail@globaledgesoft.com>
*/

/*
 * Header Guard
 */
#ifndef _HEADER_H

/*
 * Header Guard
 */
#define _HEADER_H

/**
 *@headerfile stdio.h
 */
#include<stdio.h>

/**
 *@headerfile stdlib.h
 */
#include<stdlib.h>

/**
 * @headerfile assert.h
 */
#include<assert.h>

/**
 *@def MAX
 */
#define MAX 50

/**
 *@function prototype for tower of honoi
 */
void tower_of_honoi(int, char, char, char);

int main(void)
{
    int disk; /*!@disk disk is a integer variable*/
    char *str = (char *)malloc(sizeof(char) * MAX);

    assert(str);
    printf("enter the number of disks\n");
    fgets(str, MAX, stdin);
    disk = atoi(str);
    /*function call for tower of honoi whichtakes arguments A as a source tower
     * B as destination tower and C as a auxilary tower
     */
    tower_of_honoi(disk, 'A', 'C', 'B');
    free(str);
    str = NULL;
    return 0;
#endif /*end of headerguard*/
}
void tower_of_honoi(int disk1,
	char source,
	char destination,
	char auxilary) /*function definition for tower of honoi which
			 takes arguments disk of type integer source
			 destination auxilary tower of type char which
			 returns void*/
{
    if (disk1 == 1) { /*if disk is only one move disk
			from source to destination*/
	printf("disk 1 moves from %c to %c\n", source, destination);
	return;
    } else { /*recursive call for disks to move from source to auxilary rod*/
	tower_of_honoi(disk1-1, source, auxilary, destination);
	printf("disk%d moves from %c to %c\n", disk1, source, destination);
	/*recursive call for disks to move from auxilary to destination tower*/
	tower_of_honoi(disk1-1, auxilary, destination, source);
    }
} /*end for tower of honoi function*/
