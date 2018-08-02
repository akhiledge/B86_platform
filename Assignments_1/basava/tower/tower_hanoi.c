/************Tower of hanoi program *************
 * @author : Basava Prasad S J
 * @date : 13th july 2018
 * */

///header files inclusion
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

///function declaration
void tower (int disk_num, char from_pole, char to_pole, char aux_pole);

int main (void) 
{
    ///variable declarations
    int disk_num = 0;  //number of disks
    char *str = NULL;  //to collect from stdin
    char from_pole = 'A';  //source pole
    char aux_pole = 'B';   //middle/auxillary pole
    char to_pole = 'C';  //destination pole

    /* Body of the main function and tower function call */

    str = (char *) malloc (sizeof (int));
    assert (str);        //validating nULL condition

    fprintf (stdout, "Enter the number of disks\n"); //taking input from stdin
    __fpurge (stdin);
    disk_num = atoi (fgets (str, sizeof (int), stdin)); //number of disks
    assert (str);   //validation for NULL condition

    tower (disk_num, from_pole, to_pole, aux_pole);  //calling the function

    return 0;
}

void tower (int disk_num, char from_pole, char to_pole, char aux_pole)
{
    if (disk_num == 1){  //if disk number is one move it to destination
        fprintf (stdout, "disk %d moves from %c to %c\n", disk_num, from_pole,
                                                                    to_pole);
        return;
    }
    /**Recursive function call to move the disks from source to destination *
     * If n is number of disks then number of moves is (2^n - 1)
     * Number of function calls will be (2^n+1 - 1)
     */
    tower ((disk_num - 1), from_pole, aux_pole, to_pole);
    fprintf (stdout, "disk %d moves from %c to %c\n", disk_num, from_pole,
                                                    to_pole);
    tower ((disk_num - 1), aux_pole, to_pole, from_pole);
}

