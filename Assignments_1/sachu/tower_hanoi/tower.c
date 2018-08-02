/*
 * @author Sachu George
 * @date 13/07/2018
 * @brief Program to move discs from one rod to another
 * @brief Rule 1:One disc at a time
 * @brief Rule 2:Larger disc should not come above smaller one
 * */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5  /*! Macro SIZE definition */ 

/*@brief Function definition to arrange discs
 * @param num is number of discs
 * @param A_rod is Source rod
 * @param B_rod is destination rod
 * @param temp_rod is temporary rod
 * @brief Recursive call till num reduces to 1
 * */
void tower_of_hanoi(int num, char A_rod, char B_rod, char temp_rod)
{
    if( num == 1)
    {
        printf("Moving disk from %c rod to %c rod\n", A_rod, B_rod);
        return;
    }

    tower_of_hanoi(num - 1, A_rod, temp_rod, B_rod);  ///Recursive call
    printf("Moving disk from %c rod to %c rod\n", A_rod, B_rod);
    tower_of_hanoi(num - 1, temp_rod, B_rod, A_rod);  ///Recursive call
}

int main()
{
    int num;
    char buff[SIZE];

    printf("Enter the number of disks\n"); ///Prompt from user-Number of disc
    fgets(buff, SIZE, stdin);
    num = atoi(buff);

    tower_of_hanoi(num, 'A', 'B', 'C');   ///Function call
    return 0;
}
