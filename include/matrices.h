#ifndef _MATRICES_H
#define _MATRICES_H

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "threads.h"
#include "fvectors.h"
#include "defines.h"
#include "util.h"

/**
 * Vector struct
 **/

typedef struct {
    size_t n;
    size_t m;
    f32 **elements;
} matrix;

enum multi_t {
    MATxMAT = 0,
    MATxVEC = 1
};

struct data {
    matrix A;
    union {
        vector x;
        matrix B;
    };
    union {
        vector b;
        matrix C;
    };
    enum multi_t type;
};

/**
 * Function to create a new nxm matrixrix
 **/

matrix new_matrix(size_t n, size_t m);

/**
 * Function to create a new nxm matrixrix mapped by function f
 **/

matrix new_matrix(size_t n, size_t m);

matrix matrix_construct(size_t n, size_t m, f32 val);

matrix matrix_array_construct(size_t n, size_t m, f32 *arr[]);

matrix matrix_zero(size_t n, size_t m);

matrix matrix_identity(size_t n, size_t m);

matrix matrix_fn(size_t n, size_t m, f32 **arr, f32(*f)(f32));

vector matrix_get_col(size_t col, matrix A);

vector matrix_get_row(size_t row, matrix A);

bool matrix_is_product(matrix A, matrix B, matrix C, u32 k);

/**
 * Function and macro to create a new complex vector
 **/

void printm(matrix);

/* vector functions */

// Equality

bool matrix_equal(matrix, matrix);

// Add

matrix matrix_add(matrix, matrix);

void matrix_add_to(matrix*, matrix);

// Subtract

matrix matrix_sub(matrix, matrix);

void matrix_sub_from(matrix*, matrix);

// Multi

matrix mm_multi(matrix, matrix, bool, size_t);

vector mv_multi(matrix, vector, bool, size_t);

void matrix_multi_by(matrix, matrix*);

// Transpose

void matrix_transpose(matrix*);

// Transpose

matrix matrix_copy(matrix);

// matrixrix multiplication

// Naive

void* naive(matrix, void*, enum multi_t, bool, size_t);


#endif
