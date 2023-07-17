#ifndef _VECTORS_H
#define _VECTORS_H

// Todo: Add support for complex numbers

#include <stdio.h>
#include "../defines.h"


/* MACROS */
#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )
#define VECTOR_SIZE(a,x) ( (sizeof(a)) / sizeof((a.x)))

/* N dimensional array f32 */
typedef struct {
    u32 n;
    f32 elements[];
} vector_n;

/* Undefined vectors */

extern const vector_n VECTOR_N_UNDEFINED;

/* Real unit vectors */

// Positive
extern const vector_n VECTOR_R_POS_2X_UNIT;
extern const vector_n VECTOR_R_POS_2Y_UNIT;

extern const vector_n VECTOR_R_POS_3X_UNIT;
extern const vector_n VECTOR_R_POS_3Y_UNIT;
extern const vector_n VECTOR_R_POS_3Z_UNIT;

extern const vector_n VECTOR_R_POS_4X_UNIT;
extern const vector_n VECTOR_R_POS_4Y_UNIT;
extern const vector_n VECTOR_R_POS_4Z_UNIT;
extern const vector_n VECTOR_R_POS_4W_UNIT;

// Negative
extern const vector_n VECTOR_R_NEG_2X_UNIT;
extern const vector_n VECTOR_R_NEG_2Y_UNIT;

extern const vector_n VECTOR_R_NEG_3X_UNIT;
extern const vector_n VECTOR_R_NEG_3Y_UNIT;
extern const vector_n VECTOR_R_NEG_3Z_UNIT;

extern const vector_n VECTOR_R_NEG_4X_UNIT;
extern const vector_n VECTOR_R_NEG_4Y_UNIT;
extern const vector_n VECTOR_R_NEG_4Z_UNIT;
extern const vector_n VECTOR_R_NEG_4W_UNIT;

/* Complex unit vectors */

// Positive
extern const vector_n VECTOR_C_POS_2X_UNIT;
extern const vector_n VECTOR_C_POS_2Y_UNIT;

extern const vector_n VECTOR_C_POS_3X_UNIT;
extern const vector_n VECTOR_C_POS_3Y_UNIT;
extern const vector_n VECTOR_C_POS_3Z_UNIT;

extern const vector_n VECTOR_C_POS_4X_UNIT;
extern const vector_n VECTOR_C_POS_4Y_UNIT;
extern const vector_n VECTOR_C_POS_4Z_UNIT;
extern const vector_n VECTOR_C_POS_4W_UNIT;

// Negative
extern const vector_n VECTOR_C_NEG_2X_UNIT;
extern const vector_n VECTOR_C_NEG_2Y_UNIT;

extern const vector_n VECTOR_C_NEG_3X_UNIT;
extern const vector_n VECTOR_C_NEG_3Y_UNIT;
extern const vector_n VECTOR_C_NEG_3Z_UNIT;

extern const vector_n VECTOR_C_NEG_4X_UNIT;
extern const vector_n VECTOR_C_NEG_4Y_UNIT;
extern const vector_n VECTOR_C_NEG_4Z_UNIT;
extern const vector_n VECTOR_C_NEG_4W_UNIT;

/* vector functions */

// Equality

bool m_vector_equal(vector_n, vector_n);

// Add

vector_n m_vector_add(vector_n, vector_n);

// Subtract

vector_n m_vector_sub(vector_n, vector_n);

// Multi

vector_n m_vector_multi(vector_n, vector_n);

// Dot Product

u32 m_vector_dot(vector_n, vector_n);

// Cross Product

vector_n m_vector_x(vector_n, vector_n);

#endif
