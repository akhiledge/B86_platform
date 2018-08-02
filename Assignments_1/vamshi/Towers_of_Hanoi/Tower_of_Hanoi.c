/**
 *  File name           : Tower_of_Hanoi.c
 *  Author              : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  File Creation       : 13-07-2018
 *  Created by          : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *  Last modification   : 19-07-2018
 *  Last modified by    : Vamshi Krishna Yaragani <vk.yaragani@globaledgesoft.com>
 *
 * **/

#include<stdio.h>               /// Standard I/O  header file
#include<stdlib.h>              /// Standard library
#include <assert.h> 
#include <stdio_ext.h>   

#define BUF_SIZE 50             ///Buf_size is for max size of input for user

int itr = 0;
/// Tower of Hanoi function to moves disks from one pole to another pole
void Tower_of_Hanoi (int Disk, char Src, char Dest, char Aux)
{
    itr++;
    if (Disk == 1)          /// checking wheather the moving disk is 1 or not
    {
        printf("Disk 1 moves from %c to %c\n", Src, Dest);
                ///move disk 1 from Src to Dest 
        return;
    }
    else
    {
        Tower_of_Hanoi (Disk-1, Src, Aux, Dest); /// Recursively calling the function untill disk number becomes one.
        
        printf("Disk %d moves from %c to %c\n", Disk, Src, Dest);
        
        Tower_of_Hanoi(Disk-1, Aux, Dest, Src);
    }
    
    return;
}


int main(void)
{
    int disk;       /// disk is for to take input from user number of disks.
    
    char *str = (char *)malloc(sizeof(char) * BUF_SIZE);  /// allocating the memory space for str.
    assert(str);  /// checking malloc is allocated space or not.

    printf("Enter the number of disks:\n"); 
    __fpurge(stdin);
    disk = atoi( fgets(str, BUF_SIZE, stdin) );  /// Taking the no.of disks as input from user using fgets.
    
    while( disk < 1){
        printf("No.of disks can't be negative or zero!!!!!!!!!!\n");
        __fpurge(stdin);
        printf("Enter the number of disks:\n"); 
        disk = atoi( fgets(str, BUF_SIZE, stdin) );  /// Taking the no.of disks as input from user using fgets.
    }    
    Tower_of_Hanoi(disk, 'A', 'B', 'C'); /// calling the function to move thedisks.
    printf("iterations = %d\n", itr);
    return 0;
}


