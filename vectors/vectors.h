#ifndef _VECTORS_H
#define _VECTORS_H

#include <stdio.h>
#include "../defines.h"

/**
 * Macro to get size of array
 **/

#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )

/**
 * Vector struct
 **/

typedef struct {
    u32 n;
    f32 *elements;
} m_vector;

/**
 * Function and macro to create a new vector
 **/

m_vector new_vector(u64 numArgs, ...);

#define vector(...) new_vector(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

/**
 * Function and macro to create a new complex vector
 **/

m_vector new_complex_vector(u64 numArgs, ...);

#define vector_c(...) new_complex_vector(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

void print_vec(m_vector vec);

/* vector functions */

// Equality

bool m_vector_equal(m_vector, m_vector);

// Add

m_vector m_vector_add(m_vector, m_vector);

// Subtract

m_vector m_vector_sub(m_vector, m_vector);

// Multi

m_vector m_vector_multi(m_vector, m_vector);

// Dot Product

u32 m_vector_dot(m_vector, m_vector);

// Cross Product

m_vector m_vector_x(m_vector, m_vector);

/**
 * Real unit vectors
 **/

// Positive
extern const m_vector VECTOR_R_POS_2X_UNIT;
extern const m_vector VECTOR_R_POS_2Y_UNIT;

extern const m_vector VECTOR_R_POS_3X_UNIT;
extern const m_vector VECTOR_R_POS_3Y_UNIT;
extern const m_vector VECTOR_R_POS_3Z_UNIT;

extern const m_vector VECTOR_R_POS_4X_UNIT;
extern const m_vector VECTOR_R_POS_4Y_UNIT;
extern const m_vector VECTOR_R_POS_4Z_UNIT;
extern const m_vector VECTOR_R_POS_4W_UNIT;

// Negative
extern const m_vector VECTOR_R_NEG_2X_UNIT;
extern const m_vector VECTOR_R_NEG_2Y_UNIT;

extern const m_vector VECTOR_R_NEG_3X_UNIT;
extern const m_vector VECTOR_R_NEG_3Y_UNIT;
extern const m_vector VECTOR_R_NEG_3Z_UNIT;

extern const m_vector VECTOR_R_NEG_4X_UNIT;
extern const m_vector VECTOR_R_NEG_4Y_UNIT;
extern const m_vector VECTOR_R_NEG_4Z_UNIT;
extern const m_vector VECTOR_R_NEG_4W_UNIT;

/* Complex unit vectors */

// Positive
extern const m_vector VECTOR_C_POS_2X_UNIT;
extern const m_vector VECTOR_C_POS_2Y_UNIT;

extern const m_vector VECTOR_C_POS_3X_UNIT;
extern const m_vector VECTOR_C_POS_3Y_UNIT;
extern const m_vector VECTOR_C_POS_3Z_UNIT;

extern const m_vector VECTOR_C_POS_4X_UNIT;
extern const m_vector VECTOR_C_POS_4Y_UNIT;
extern const m_vector VECTOR_C_POS_4Z_UNIT;
extern const m_vector VECTOR_C_POS_4W_UNIT;

// Negative
extern const m_vector VECTOR_C_NEG_2X_UNIT;
extern const m_vector VECTOR_C_NEG_2Y_UNIT;

extern const m_vector VECTOR_C_NEG_3X_UNIT;
extern const m_vector VECTOR_C_NEG_3Y_UNIT;
extern const m_vector VECTOR_C_NEG_3Z_UNIT;

extern const m_vector VECTOR_C_NEG_4X_UNIT;
extern const m_vector VECTOR_C_NEG_4Y_UNIT;
extern const m_vector VECTOR_C_NEG_4Z_UNIT;
extern const m_vector VECTOR_C_NEG_4W_UNIT;

#endif
