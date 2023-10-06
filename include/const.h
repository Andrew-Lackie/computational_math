#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/* Basic utility macros */
#define MIN(a,b) ({ \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		(((_a) < (_b)) ? (_a) : (_b)); }) \

#define MAX(a,b) ({ \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		(((_a) > (_b)) ? (_a) : (_b)); \
		 }) \

#define ABS(a) ((f32) a < 0.0f ? -(a) : (a))

/* Constants */

// pi ratios defined
#define M_PI 3.1415926535897f
#define M_2PI (2.0f * T_PI)

#define M_HALF_PI (T_PI / 2.0f)
#define M_THIRD_PI (T_PI / 3.0f)
#define M_QUARTER_PI (T_PI / 4.0f)
#define M_SIXTH_PI (T_PI / 6.0f)

#define M_ONE_OVER_PI (1.0f / T_PI)
#define M_ONE_OVER_2PI (1.0f / T_2PI)

// roots defined
#define M_SQRT_TWO 1.4142135623730f
#define M_SQRT_ONE_OVER_TWO 0.7071067811865f

#define M_SQRT_THREE 1.7320508075688f
#define M_SQRT_ONE_OVER_THREE 0.5773502691896f

#define M_SQRT_FIVE 2.2360679774997f

// eulers constants
#define M_EULER_NUM 2.7182818284590
#define M_EULER_CONST 0.5772156649015

// convert degrees to radians
#define M_DEG2RAD_MULTI (T_PI / 180.0f)

// convert radians to degrees
#define M_RAD2DEG_MULTI (180.f / T_PI)

// infinity defined
#define M_INFINITY (1e30f * 1e30f)

// epsilon defined
#define M_EPSILON 1.192092896e-07f

#endif
