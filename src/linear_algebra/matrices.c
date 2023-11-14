#include <matrices.h>

/* vector functions */

// New vector

matrix new_matrix(size_t n, size_t m)
{

    matrix matrix = { .n = n, .m = m };

    f32** block_v = m_allocate(n * sizeof(f32*), MEMORY_TAG_MATRIX);

    for (size_t i = 0; i < n; i++) {
        block_v[i] = m_allocate(m * sizeof(f32), MEMORY_TAG_MATRIX);
    }

    matrix.elements = block_v;

    return matrix;
}

void free_matrix(matrix* A)
{
    size_t size = (A->n * sizeof(f32) + (A->m * sizeof(f32)));
    void* block = (void*) A->elements;
    m_free(block, size, MEMORY_TAG_MATRIX);
}

matrix matrix_construct(size_t n, size_t m, f32 val)
{

    matrix a = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            a.elements[i][j] = val;
        }
    }

    return a;
}

matrix matrix_array_construct(size_t n, size_t m, f32 *arr[])
{

    matrix a = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            a.elements[i][j] = arr[i][j];
        }
    }

    return a;
}

matrix matrix_zero(size_t n, size_t m)
{

    matrix zero = new_matrix(n, m);

    return zero;
}

matrix matrix_identity(size_t n, size_t m)
{

    if (n != m) {
	      LOG_ERROR("Action undefined on non square matrixrices: rows %f and columns %f", n, m);
        exit(1);
    }

    matrix id = new_matrix(n, m);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            id.elements[i][j] = (i == j) ? 1 : 0;
        }
    }

    return id;
}

vector matrix_get_col(size_t col, matrix A)
{

    col--;

    VECTOR_INIT(v, A.n);

    for (size_t i = 0; i < A.n; i++) {
        v.vector_list.elements[i] = (void*)&A.elements[i][col];
    }

    return v;

}

vector matrix_get_row(size_t row, matrix A)
{

    row--;

    VECTOR_INIT(v, A.m);

    for (size_t i = 0; i < A.m; i++) {
        v.vector_list.elements[i] = (void*)&A.elements[row][i];
    }

    return v;
}

void printm(matrix matrix)
{

    for (size_t i = 0; i < matrix.n; i++) {
        for (size_t j = 0; j < matrix.m; j++) {

            printf("%f", matrix.elements[i][j]);
            if (j < matrix.n - 1) {
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

void matrix_transpose(matrix* A)
{

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

bool matrix_equal(matrix A, matrix B)
{

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

static bool freivald(matrix A, matrix B, matrix C)
{

    if (A.n != B.n || A.m != B.m) {
	      LOG_ERROR("Freivald's algorithm is only defined on square matrixrices of equal dimensions");
        exit(1);
    }

    u32 N = A.n;

    f32 element;

    vector r = fvector_zero_construct(N);

    for (size_t i = 0; i < N; i++) {
        element = randint(2);
        r.vector_list.elements[i] = (void*) &element;
    }

    vector br = fvector_zero_construct(N);

    f32 el1;

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            el1 = *(f32*)br.vector_list.elements[i] + B.elements[i][j] * *(f32*)r.vector_list.elements[j];
            br.vector_list.elements[i] = (void*)&el1;
        }
    }

    // expression A * (B*r) - (C*r)
    vector cr = fvector_zero_construct(N);

    f32 el2;

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++) {
            el2 = *(f32*)cr.vector_list.elements[i] + C.elements[i][j] * *(f32*)r.vector_list.elements[j];
            cr.vector_list.elements[i] = (void*)&el2;
        }

    // expression A * (B*r) - (C*r)
    VECTOR_INIT(axbr, N);
    f32 el3;

    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++) {
            el3 = *(f32*)axbr.vector_list.elements[i] + A.elements[i][j] * *(f32*)br.vector_list.elements[j];
            axbr.vector_list.elements[i] = (void*)&el3;
        }
    // A * (B*r) - (C*r) is 0 or not

    for (size_t i = 0; i < N; i++)
        if (axbr.vector_list.elements[i] - cr.vector_list.elements[i] != 0) {
            return false;
        }
    vector_free(&r);
    vector_free(&br);
    vector_free(&cr);
    vector_free(&axbr);
    return true;
}

// Check if C is the product of AB

bool matrix_is_product(matrix A, matrix B, matrix C, u32 k)
{
    for (size_t i = 0; i < k; i++)
        if (freivald(A, B, C) == false)
            return false;
    return true;
}

// Add

matrix matrix_add(matrix A, matrix B)
{

    if (A.n != B.n && A.m != B.m) {
	      LOG_ERROR("Action undefined on matrixrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    matrix sum = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            sum.elements[i][j] = A.elements[i][j] + B.elements[i][j];
        }
    }
    return sum;
}

void matrix_add_to(matrix *A, matrix B)
{
    if (A->n != B.n) {
	      LOG_ERROR("Action undefined on matrixrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A->n, B.n, A->m, B.m);
        exit(1);
    }

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = 0; j < A->m; j++) {
            A->elements[i][j] = A->elements[i][j] + B.elements[i][j];
        }
    }
}

// Subtract

matrix matrix_sub(matrix A, matrix B)
{
    if (A.n != B.n) {
	      LOG_ERROR("Action undefined on matrixrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A.n, B.n, A.m, B.m);
        exit(1);
    }

    matrix diff = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            diff.elements[i][j] = A.elements[i][j] - B.elements[i][j];
        }
    }
    return diff;
}

void matrix_sub_from(matrix *A, matrix B)
{
    if (A->n != B.n) {
	      LOG_ERROR("Action undefined on matrixrices of different sizes: n1: %f, n2: %f and m1: %f, m2: %f", A->n, B.n, A->m, B.m);
        exit(1);
    }

    for (size_t i = 0; i < A->n; i++) {
        for (size_t j = 0; j < A->m; j++) {
            A->elements[i][j] = A->elements[i][j] - B.elements[i][j];
        }
    }
}

matrix matrix_copy(matrix A)
{

    matrix cpy = new_matrix(A.n, A.m);

    for (size_t i = 0; i < A.n; i++) {
        for (size_t j = 0; j < A.m; j++) {
            cpy.elements[i][j] = A.elements[i][j];
        }
    }

    return cpy;
}
