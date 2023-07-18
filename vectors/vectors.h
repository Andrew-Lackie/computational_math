#ifndef _VECTORS_H
#define _VECTORS_H

#include <stdio.h>
#include "../defines.h"

/**
 * Macro to get size of array
 **/

#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )

/**
 * Memory Allocator
 **/

/**
 * N dimensional array f32
 **/

typedef struct {
    u32 n;
    f32 *elements;
} m_vector;

/**
 * Memory allocator
 **/

m_vector allocate(u64 size);

/**
 * Memory allocator with default value
 **/

m_vector construct_default(u64 size, f32 val);

/**
 * Memory allocator for empty array
 **/

m_vector construct_empty(u64 size);

/**
 * Function to create a new vector
 **/

m_vector new_m_vector(u32 numArgs, ...);

/**
 * Macros to allocate custom type dynamically allocated vectors
 **/

#define NUM_ARGS(type, ...) (((type[]){0.0f, ##__VA_ARGS__}) / (sizeof(type) - 1))
#define vector(...) new_m_vector(NUM_ARGS(__VA_ARGS__), ##__VA_ARGS__)

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

#endif
