#ifndef _IVECTORS_H
#define _IVECTORS_H

#include <defines.h>
#include <stdint.h>
#include <memory.h>
#include <vectors.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define ARRAY_SIZE(a) ( (sizeof(a)) / sizeof((a.elements[0])) )

/**
 * Create new ivector
 **/
vector new_ivector(size_t dim);

/**
 * Free ivector
 **/
void free_ivector(vector* A);

/**
 * ivector constructors
 **/
vector ivector_va_list_construct(size_t num_args, ...);
#define ivector(...) ivector_va_list_construct(NUMARGS(i32, __VA_ARGS__), ##__VA_ARGS__)

vector ivector_default_construct(size_t dim, i32 val);
vector ivector_zero_construct(size_t dim);
vector ivector_array_construct(size_t dim, i32 arr[]);

/**
 * ivector string conversion and printing
 **/
void printiv(vector v);
char* ivector_to_str(vector v);

/**
 * Copy a ivectortor
 **/
vector ivector_copy(vector v);
vector ivector_copy_ptr(vector *v);

/**
 * ivectortor operations
 **/

void ivector_fn(vector *v, i32 (*f)(i32));

bool ivector_equal(vector, vector);

vector ivector_add(vector, vector);
void ivector_add_to(vector*, vector);

vector ivector_subtract(vector, vector);
void ivector_subtract_from(vector*, vector);

void ivector_scale(vector*, i32);

void ivector_scalar_divide(vector*, i32);

vector ivector_multiply(vector, vector);
void ivector_multiply_by(vector*, vector);

u32 ivector_dot(vector, vector);
vector ivector_cross(vector, vector);

bool ivector_orthogonal(vector, vector);

i32 ivector_magnitude_squared(vector v);
i32 ivector_magnitude(vector v);

void ivector_normalize(vector *v);

#endif
