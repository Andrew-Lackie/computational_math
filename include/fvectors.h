#ifndef _FVECTORS_H
#define _FVECTORS_H

#include <defines.h>
#include <memory.h>
#include <vectors.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )

/**
 * Create new fvector
 **/
vector new_fvector(size_t dim);

/**
 * Free fvector
 **/
void free_fvector(vector* A);

/**
 * fvector constructors
 **/
vector fvector_va_list_construct(size_t num_args, ...);
#define fvector(...) fvector_va_list_construct(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

vector fvector_default_construct(size_t dim, f32 val);
vector fvector_zero_construct(size_t dim);
vector fvector_array_construct(size_t dim, f32 arr[]);

/**
 * fvector string conversion and printing
 **/
void printfv(vector v);
char* fvector_to_str(vector v);

/**
 * Copy a fvectortor
 **/
vector fvector_copy(vector v);
vector fvector_copy_ptr(vector *v);

/**
 * fvectortor operations
 **/

void fvector_fn(vector *v, f32 (*f)(f32));

bool fvector_equal(vector, vector);

vector fvector_add(vector, vector);
void fvector_add_to(vector*, vector);

vector fvector_subtract(vector, vector);
void fvector_subtract_from(vector*, vector);

void fvector_scale(vector*, f32);

void fvector_scalar_divide(vector*, f32);

vector fvector_multiply(vector, vector);
void fvector_multiply_by(vector*, vector);

u32 fvector_dot(vector, vector);
vector fvector_cross(vector, vector);

bool fvector_orthogonal(vector, vector);

f32 fvector_magnitude_squared(vector v);
f32 fvector_magnitude(vector v);

void fvector_normalize(vector *v);

#endif
