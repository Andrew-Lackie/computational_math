#ifndef _MATRICES_H
#define _MATRICES_H

#include "../vectors/vectors.h"
#include <stdio.h>
#include "../../defines.h"

/**
 * Vector struct
 **/

typedef struct {
    size_t n;
    size_t m;
    f32 **elements;
} mat;

/**
 * Function to create a new nxm matrix
 **/

mat new_matrix(size_t n, size_t m);

/**
 * Function to create a new nxm matrix mapped by function f
 **/

mat new_matrix(size_t n, size_t m);

mat mat_construct(size_t n, size_t m, f32 val);

mat mat_array_construct(size_t n, size_t m, f32 *arr[]);

mat mat_zero(size_t n, size_t m);

mat mat_identity(size_t n, size_t m);

mat mat_fn(size_t n, size_t m, f32 **arr, f32(*f)(f32));

vec mat_get_col(size_t col, mat A);

vec mat_get_row(size_t row, mat A);

bool mat_is_product(mat A, mat B, mat C, u32 k);

/**
 * Function and macro to create a new complex vector
 **/

void printm(mat);

/* vector functions */

// Equality

bool mat_equal(mat, mat);

// Add

mat mat_add(mat, mat);

void mat_add_to(mat*, mat);

// Subtract

mat mat_sub(mat, mat);

void mat_sub_from(mat*, mat);

// Multi

mat mat_multi(mat, mat);

void mat_multi_by(mat, mat*);

// Transpose

void mat_transpose(mat*);

#endif
