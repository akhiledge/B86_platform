/**
 * File              : header/tower.h
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 15.07.2018
 * Last Modified Date: 19.07.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */

/// Header Guard
#ifndef _TOWER_H

#define _TOWER_H

/// Macros for the project

#define MAX_BIZ 64

// Macros ends.....

// Prototypes and typedef 
/**
 * @Synopsis  
 *
 * @Param disc
 * @Param src_tower
 * @Param dest_tower
 * @Param mid_tower
 *
 * @Returns void
 */
extern void 
hanoi_tower (int32_t disc,
             char src_tower,
             char dest_tower,
             char mid_tower 
             );
// ends ....
 
#endif      /// Header Guard ends .....
