#include <matrices.h>

matrix mm_multi(matrix A, matrix B, bool mthread, size_t params)
{

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %d, l: %d and l: %d, m: %d", A.n, B.m, A.m, B.n);
        exit(1);
    }

    void* c = naive(A, (void*)&B, MATxMAT, mthread, params);

    return *(matrix*)c;
}

vector mv_multi(matrix A, vector x, bool mthread, size_t params)
{

    if ((i32)A.m != VECTOR_TOTAL(x)) {
	      LOG_ERROR("Incompatible sizes; matrix size: %dx%d, vector size: %d", A.n, A.m, VECTOR_TOTAL(x));
        exit(1);
    }

    void* c = naive(A, (void*)&x, MATxVEC, mthread, params);

    return *(vector*)c;
}
