#include "matrices.h"

/* vector functions */

// New vector

mat new_matrix(size_t n, size_t m) {

    mat matrix = { .n = n, .m = m };

    f32** block_v = m_allocate(n * sizeof(f32*), MEMORY_TAG_MATRIX);

    for (size_t i = 0; i < n; i++) {
        block_v[i] = m_allocate(m * sizeof(f32), MEMORY_TAG_MATRIX);
    }

    matrix.elements = block_v;

    return matrix;
}

mat mat_construct(size_t n, size_t m, f32 val) {

    mat a = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            a.elements[i][j] = val;
        }
    }

    return a;
}

mat mat_array_construct(size_t n, size_t m, f32 *arr[]) {

    mat a = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            a.elements[i][j] = arr[i][j];
        }
    }

    return a;
}

mat mat_zero(size_t n, size_t m) {

    mat zero = new_matrix(n, m);

    return zero;
}

mat mat_identity(size_t n, size_t m) {

    if (n != m) {
	      LOG_ERROR("Action undefined on non square matrices: rows %f and columns %f", n, m);
        exit(1);
    }

    mat id = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            id.elements[i][j] = (i == j) ? 1 : 0;
        }
    }

    return id;
}

vec mat_get_col(size_t col, mat A) {

    col--;

    vec v = new_vector(A.n);

    for (size_t i = 0; i < A.n; i++) {
        v.elements[i] = A.elements[i][col];
    }

    return v;

}

vec mat_get_row(size_t row, mat A) {

    row--;

    vec v = new_vector(A.m);

    for (size_t i = 0; i < A.m; i++) {
        v.elements[i] = A.elements[row][i];
    }

    return v;
}

void printm(mat mat) {

    for (size_t i = 0; i < mat.n; i++) {
        for (size_t j = 0; j < mat.m; j++) {

            printf("%f", mat.elements[i][j]);
            if (j < mat.n - 1) {
                printf(" ");
            }
            else {
                printf(" ");
            }
        }
        printf("\n\n");
    }
}

// Transpose

void mat_transpose(mat* A) {

    f32 temp;

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = i + 1; j < A->m; j++) {
            temp = A->elements[i][j];
            A->elements[i][j] = A->elements[j][i];
            A->elements[j][i] = temp;
        }
    }
}

// Equality

bool mat_equal(mat A, mat B) {

    if (A.n != B.n && A.m != B.m) {return false;}

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; i++) {
            if (A.elements[i][j] != B.elements[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Freivalds’ algorithm

static bool freivald(mat A, mat B, mat C) {

    if (A.n != B.n || A.m != B.m) {
	      LOG_ERROR("Freivald's algorithm is only defined on square matrices of equal dimensions");
        exit(1);
    }

    u32 N = A.n;

    vec r = vec_zero_construct(N);

    for (size_t i = 0; i < N; i++) {
        r.elements[i] = (f32) randint(2);
    }

    vec br = vec_zero_construct(N);

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            br.elements[i] = br.elements[i] + B.elements[i][j] * r.elements[j];

    // expression A * (B*r) - (C*r)
    vec cr = vec_zero_construct(N);

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            cr.elements[i] = cr.elements[i] + C.elements[i][j] * r.elements[j];

    // expression A * (B*r) - (C*r)
    vec axbr = vec_zero_construct(N);

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            axbr.elements[i] = axbr.elements[i] + A.elements[i][j] * br.elements[j];

    // A * (B*r) - (C*r) is 0 or not
    for (size_t i = 0; i < N; i++)
        if (axbr.elements[i] - cr.elements[i] != 0) {
            return false;
        }
    free_vector(&r);
    free_vector(&br);
    free_vector(&cr);
    free_vector(&axbr);
    return true;
}

// Check if C is the product of AB

bool mat_is_product(mat A, mat B, mat C, u32 k) {
    for (size_t i = 0; i < k; i++)
        if (freivald(A, B, C) == false)
            return false;
    return true;
}

// Add

mat mat_add(mat A, mat B) {

    if (A.n != B.n && A.m != B.m) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    mat sum = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            sum.elements[i][j] = A.elements[i][j] + B.elements[i][j];
        }
    }
    return sum;
}

void mat_add_to(mat *A, mat B) {
    if (A->n != B.n) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A->n, B.n, A->m, B.m);
        exit(1);
    }

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = 0; j < A->m; j++) {
            A->elements[i][j] = A->elements[i][j] + B.elements[i][j];
        }
    }
}

// Subtract

mat mat_sub(mat A, mat B) {
    if (A.n != B.n) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    mat diff = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            diff.elements[i][j] = A.elements[i][j] - B.elements[i][j];
        }
    }
    return diff;
}

void mat_sub_from(mat *A, mat B) {
    if (A->n != B.n) {
	      LOG_ERROR("Action undefined on matrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A->n, B.n, A->m, B.m);
        exit(1);
    }

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = 0; j < A->m; j++) {
            A->elements[i][j] = A->elements[i][j] - B.elements[i][j];
        }
    }
}

mat mat_copy(mat A) {

    mat cpy = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            cpy.elements[i][j] = A.elements[i][j];
        }
    }

    return cpy;
}
