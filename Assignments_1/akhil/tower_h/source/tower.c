/**
 * File              : src_tower/tower.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */

#include "./../header/standard.h"
#include "./../header/tower.h"



/**
 * @Synopsis  hanoi_tower is the function which will display the disc exchange
 *            recursively
 *
 * @Param disc --> disc is an integer which imples No.of discs
 * @Param src_tower --> source tower 'A'
 * @Param dest_tower --> destination tower 'C'
 * @Param mid_tower  --> temp tower 'B'
 *
 * @Returns  void
 *
 */

void
hanoi_tower(int32_t disc,
	     char src_tower,
	     char dest_tower,
	     char mid_tower
	     )
{
    if (disc == 1) {
       /** Printing the final output of the function when reach condition */
	    printf("%10d | %-5c | %-5c |\n", 1, src_tower, dest_tower);
	return;
    } else {
	/** Recursive call of hanoi_tower function */
	hanoi_tower(disc-1, src_tower, mid_tower, dest_tower);
	printf("%10d | %-5c | %-5c |\n", disc, src_tower, dest_tower);
	hanoi_tower(disc-1, mid_tower, dest_tower, src_tower);
    }
}
