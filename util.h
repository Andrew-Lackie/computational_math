#ifndef _M_ALGO_H
#define _M_ALGO_H

#include "defines.h"

/* Carmack's fast square root algorithm */
f32 m_sqrt(f32 num) {
	 i32 i;
	 f32 x, y;
	 x = num* 0.5f;
	 y = num;
	 i  = * (i32*) &y; 						// evil floating point bit level hacking
	 i  = 0x5f3759df - (i >> 1);  // what the fuck?
	 y  = * (f32 * ) &i;
	 y  = y * (1.5f - (x * y * y ));
	 y  = y * (1.5f - (x * y * y ));
	 return num* y;
}

#endif
