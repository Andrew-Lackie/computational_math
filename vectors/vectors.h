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
    size_t n;
    f32 *elements;
} m_vector;

/**
 * Function and macro to create a new vector
 **/

m_vector new_vector(size_t num_args, ...);
#define vector(...) new_vector(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

/**
 * Function to create a new n dimensional vector
 **/

m_vector vector_n(size_t dim, f32 *arr);

/**
 * Creates a dynamically allocated vector and performs an operation on each element
 **/

m_vector vector_f(size_t dim, f32 *arr, f32 (*f)(f32));

/**
 * Function and macro to create a new complex vector
 **/

void print_v(m_vector vec);

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

// Init vector constants

void initialize_vectors();


#endif
