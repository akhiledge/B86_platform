/*
 * File              : Tower_of_Hanoi.c
<<<<<<< HEAD
 * Author            : Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 24.08.2018
 * Last Modified By  : Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio_ext.h>

#define BUF_SIZE 50


/**
 * @Synopsis  --->  Tower_of_Hanoi function to move disks from src to 
 *                  dest using Auxiliary tower. 
=======
 * Author            : Yaragani Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 * Date              : 16.07.2018
 * Last Modified Date: 23.08.2018
 * Last Modified By  : Yaragani Vamshi Krishna <vk.yaragani@globaledgesoft.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio_ext.h>

#define BUF_SIZE 50


/**
 * @Synopsis  --->  Tower_of_Hanoi function to move disks from src to dest using
 *                  Auxiliary tower 
>>>>>>> master
 *
 * @Param Disk ---> It is to know which disk is moving
 * @Param Src  ---> It is to know disk's source tower
 * @Param Dest ---> It is to know disk's destination tower
 * @Param Aux  ---> It is to know which is the temporary tower
 */
void
Tower_of_Hanoi (int Disk, 
                char Src, 
                char Dest, 
                char Aux)
{
    /**
     * @Synopsis  ---> Checking wheather the moving disk is 1 or not
     *
     * @Param Disk ---> to know the disk number
     */
    if (Disk == 1) {
        printf("Disk 1 moves from %c to %c\n", Src, Dest);
        return;
    } else {
        Tower_of_Hanoi (Disk-1, Src, Aux, Dest);
        printf("Disk %d moves from %c to %c\n", Disk, Src, Dest);
        Tower_of_Hanoi(Disk-1, Aux, Dest, Src);
    }
    return;
} /** End of Tower_of_Hanoi function */

/**
 * @Synopsis ---> Tower of Hanoi main function
 *
 * @Returns  ---> it is returning 0 to the startup function
 */
int main (void)
{
    /**
     * @Param disk ---> To take the input from user no.of disks
     */
    int disk;
<<<<<<< HEAD
    char src_tower = 'A';
    char dst_tower;
    char aux_tower;
=======
>>>>>>> master
    char *str = (char *)malloc(sizeof(char) * BUF_SIZE);
    assert(str);
    printf("Enter the number of disks:\n");
    __fpurge(stdin);
    disk = atoi( fgets(str, BUF_SIZE, stdin) );
<<<<<<< HEAD
    free(str);
    str = NULL;
=======
>>>>>>> master
    
    /**
     * @Synopsis  ---> Checking wheather user input is valid or not
     */
    while (disk < 1) {
        printf("No.of disks can't be negative or zero!!!!!!!!!!\n");
        __fpurge(stdin);
        printf("Enter the number of disks:\n"); 
        disk = atoi( fgets(str, BUF_SIZE, stdin) );
    }
<<<<<<< HEAD
    printf("Enter the Destination tower(B or C):");
    __fpurge(stdin);
    dst_tower = getchar();
    switch (dst_tower) {
    case 'B':
        aux_tower = 'C';
        break;
    case 'C':
        aux_tower = 'B';
        break;
    default :
        printf("dst_tower should not be different from B or C!!!!!\n");
        return 0;
    }
    Tower_of_Hanoi(disk, 'A', dst_tower, aux_tower);
=======
    Tower_of_Hanoi(disk, 'A', 'B', 'C');
>>>>>>> master
    return 0;
}
