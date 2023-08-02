#include <strings.h>
#include <stdlib.h>
#include "vectors.h"
#include <stdarg.h>
#include "../memory/memory.h"
#include "matrices.h"

/* vector functions */

// New vector

m_matrix new_matrix(size_t n, size_t m, ...) {

    m_matrix mat = { .n = n, .m = m };

    void* block_v = m_allocate(n * m * sizeof(f32), MEMORY_TAG_MATRIX);
    f32** block_f = (f32**) block_v;

    mat.vectors = block_f;

    va_list list;
    va_start(list, m);

    for (size_t i = 0; i < m; i++) {
        mat.vectors[i] = va_arg(list, float*);
    }

    return mat;
}

m_matrix matrix_nm(size_t n, size_t m, f32 **arr) {

    m_matrix mat = { .n = n, .m = m };

    void* block_v = m_allocate(n * m * sizeof(f32), MEMORY_TAG_MATRIX);
    f32** block_f = (f32**) block_v;

    /*Replace the following with m_copy_memory eventually*/
    /*m_copy_memory(block_f, arr, dim);*/

    for (size_t i = 0; i < m; i++) {
        block_f[i] = arr[i];
    }

    mat.vectors = block_f;

    return mat;
}

void print_m(m_matrix mat) {
    printf("[ ");

    for (size_t i = 0; i < mat.n; i++) {
        printf("[ ");
        for (size_t j = 0; j < mat.m; j++) {

            printf("%f", mat.vectors[i][j]);
            if (j < mat.n - 1) {
                printf(", ");
            }
            else {
                printf(" ");
            }
        }
        printf("]\n");
    }
    printf("]\n");
}

// Equality

bool m_matrix_equal(m_matrix A, m_matrix B) {

    if (A.n != B.n && A.m != B.m) {return false;}

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; i++) {
            if (A.vectors[i][j] != B.vectors[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Add

m_matrix m_matrix_add(m_matrix A, m_matrix B) {

    if (A.n != B.n && A.m != B.m) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    m_matrix sum = { .n = A.n, .m = A.m };

    void* block_v = m_allocate(A.n * A.m * sizeof(f32), MEMORY_TAG_MATRIX);
    f32** block_f = (f32**) block_v;

    sum.vectors = block_f;

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            sum.vectors[i][j] = A.vectors[i][j] + B.vectors[i][j];
        }
    }
    return sum;
}

// Subtract

m_matrix m_matrix_sub(m_matrix A, m_matrix B) {
    if (A.n != B.n) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    m_matrix diff = { .n = A.n, .m = A.m };

    void* block_v = m_allocate(A.n * A.m * sizeof(f32), MEMORY_TAG_MATRIX);
    f32** block_f = (f32**) block_v;

    diff.vectors = block_f;

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            diff.vectors[i][j] = A.vectors[i][j] - B.vectors[i][j];
        }
    }
    return diff;
}

// Multi

m_matrix m_matrix_multi(m_matrix A, m_matrix B) {

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %f, l: %f and l: %f, m: %f", A.n, B.m, A.m, B.n);
        exit(1);
    }

    m_matrix multi = { .n = A.n, .m = B.m };

    void* block_v = m_allocate(A.n * B.m * sizeof(f32), MEMORY_TAG_MATRIX);
    f32** block_f = (f32**) block_v;

    multi.vectors = block_f;

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            multi.vectors[i][j] = A.vectors[i][j] * B.vectors[j][i];
        }
    }
    return multi;
}

void m_matrix_transpose(m_matrix* A) {

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = 0; j < A->m; j++) {
            A->vectors[i][j] = A->vectors[j][i];
        }
    }
}
