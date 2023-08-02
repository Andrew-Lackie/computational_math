#ifndef _MATRICES_H
#define _MATRICES_H

#include "vectors.h"
#include <stdio.h>
#include "../defines.h"

/**
 * Vector struct
 **/

typedef struct {
    size_t n;
    size_t m;
    f32 **vectors;
} m_matrix;

/**
 * Function and macro to create a new vector
 **/

m_matrix new_matrix(size_t n, size_t m, ...);
#define matrix(...) new_matrix(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

/**
 * Function to create a new nxm matrix
 **/

m_matrix matrix_nm(size_t n, size_t m, f32 **arr);

/**
 * Function to create a new nxm matrix mapped by function f
 **/

m_matrix matrix_f(size_t n, size_t m, f32 **arr, f32(*f)(f32));

/**
 * Function and macro to create a new complex vector
 **/

void print_m(m_matrix);

/* vector functions */

// Equality

bool m_matrix_equal(m_matrix, m_matrix);

// Add

m_matrix m_matrix_add(m_matrix, m_matrix);

// Subtract

m_matrix m_matrix_sub(m_matrix, m_matrix);

// Multi

m_matrix m_matrix_multi(m_matrix, m_matrix);

// Transpose

void m_matrix_transpose(m_matrix*);

/* Identity matrices */

/*extern const matrix_nm MATRIX_2_IDENTITY;*/
/*extern const matrix_nm MATRIX_3_IDENTITY;*/
/*extern const matrix_nm MATRIX_4_IDENTITY;*/
/*extern const matrix_nm matrix_nm_IDENTITY;*/

/*[> pauli matrices <]*/
/*extern const matrix_nm MATRIX_2_PAULI_SIG1[2][2];*/
/*extern const matrix_nm MATRIX_2_PAULI_SIG2[2][2];*/
/*extern const matrix_nm MATRIX_2_PAULI_SIG3[2][2];*/

#endif
