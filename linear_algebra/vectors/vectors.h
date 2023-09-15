#ifndef _VECTORS_H
#define _VECTORS_H

#include "../../defines.h"
#include "../../memory/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )

/**
 * Vector struct
 **/
typedef struct {
    f32 *elements;
    size_t n;
} vec;

/**
 * Create new vector
 **/
vec new_vector(size_t dim);

/**
 * Free vector
 **/
void free_vector(vec* A);

/**
 * Vector constructors
 **/
vec vec_va_list_construct(size_t num_args, ...);
#define vector(...) vec_va_list_construct(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

vec vec_default_construct(size_t dim, f32 val);
vec vec_zero_construct(size_t dim);
vec vec_array_construct(size_t dim, f32 arr[]);

/**
 * vector string conversion and printing
 **/
void printv(vec v);
char* vec_to_str(vec v);

/**
 * Copy a vector
 **/
vec vec_copy(vec v);
vec vec_copy_ptr(vec *v);

/**
 * Vector operations
 **/

void vec_fn(vec *v, f32 (*f)(f32));

bool vec_equal(vec, vec);

vec vec_add(vec, vec);
void vec_add_to(vec*, vec);

vec vec_subtract(vec, vec);
void vec_subtract_from(vec*, vec);

void vec_scalar_multiply(vec*, f32);

void vec_scalar_divide(vec*, f32);

vec vec_multiply(vec, vec);
void vec_multiply_by(vec*, vec);

u32 vec_dot(vec, vec);
vec vec_cross(vec, vec);

bool vec_orthogonal(vec, vec);

f32 vec_magnitude_squared(vec v);
f32 vec_magnitude(vec v);

void vec_normalize(vec *v);

/**
 * Real unit vectors
 **/

// Positive
extern const vec VECTOR_R_POS_2X_UNIT;
extern const vec VECTOR_R_POS_2Y_UNIT;

extern const vec VECTOR_R_POS_3X_UNIT;
extern const vec VECTOR_R_POS_3Y_UNIT;
extern const vec VECTOR_R_POS_3Z_UNIT;

extern const vec VECTOR_R_POS_4X_UNIT;
extern const vec VECTOR_R_POS_4Y_UNIT;
extern const vec VECTOR_R_POS_4Z_UNIT;
extern const vec VECTOR_R_POS_4W_UNIT;

// Negative
extern const vec VECTOR_R_NEG_2X_UNIT;
extern const vec VECTOR_R_NEG_2Y_UNIT;

extern const vec VECTOR_R_NEG_3X_UNIT;
extern const vec VECTOR_R_NEG_3Y_UNIT;
extern const vec VECTOR_R_NEG_3Z_UNIT;

extern const vec VECTOR_R_NEG_4X_UNIT;
extern const vec VECTOR_R_NEG_4Y_UNIT;
extern const vec VECTOR_R_NEG_4Z_UNIT;
extern const vec VECTOR_R_NEG_4W_UNIT;

/* Complex unit vectors */

// Positive
extern const vec VECTOR_C_POS_2X_UNIT;
extern const vec VECTOR_C_POS_2Y_UNIT;

extern const vec VECTOR_C_POS_3X_UNIT;
extern const vec VECTOR_C_POS_3Y_UNIT;
extern const vec VECTOR_C_POS_3Z_UNIT;

extern const vec VECTOR_C_POS_4X_UNIT;
extern const vec VECTOR_C_POS_4Y_UNIT;
extern const vec VECTOR_C_POS_4Z_UNIT;
extern const vec VECTOR_C_POS_4W_UNIT;

// Negative
extern const vec VECTOR_C_NEG_2X_UNIT;
extern const vec VECTOR_C_NEG_2Y_UNIT;

extern const vec VECTOR_C_NEG_3X_UNIT;
extern const vec VECTOR_C_NEG_3Y_UNIT;
extern const vec VECTOR_C_NEG_3Z_UNIT;

extern const vec VECTOR_C_NEG_4X_UNIT;
extern const vec VECTOR_C_NEG_4Y_UNIT;
extern const vec VECTOR_C_NEG_4Z_UNIT;
extern const vec VECTOR_C_NEG_4W_UNIT;

// Init vector constants

void initialize_vectors();


#endif
