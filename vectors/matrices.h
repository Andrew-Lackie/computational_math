#ifndef _MATRICES_H
#define _MATRICES_H

#include "vectors.h"

typedef struct {
    u32 row;
    u32 column;
    vector_n **mat;
} matrix_nm;

/* Identity matrices */

extern const matrix_nm MATRIX_2_IDENTITY;
extern const matrix_nm MATRIX_3_IDENTITY;
extern const matrix_nm MATRIX_4_IDENTITY;
extern const matrix_nm matrix_nm_IDENTITY;

/* pauli matrices */
extern const matrix_nm MATRIX_2_PAULI_SIG1[2][2];
extern const matrix_nm MATRIX_2_PAULI_SIG2[2][2];
extern const matrix_nm MATRIX_2_PAULI_SIG3[2][2];

// Add

matrix_nm m_matrix_add(matrix_nm, matrix_nm);

// Subtract

matrix_nm m_matrix_sub(matrix_nm, matrix_nm);

// Multi

matrix_nm m_matrix_multi(matrix_nm, matrix_nm);

// Equality

matrix_nm m_matrix_equal(matrix_nm, matrix_nm);

// Transpose

matrix_nm m_matrix_trans(matrix_nm, matrix_nm);

#endif
