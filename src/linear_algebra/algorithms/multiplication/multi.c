#include <matrices.h>

mat mm_multi(mat A, mat B, bool mthread, size_t params) {

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %d, l: %d and l: %d, m: %d", A.n, B.m, A.m, B.n);
        exit(1);
    }

    void* c = naive(A, (void*)&B, MATxMAT, mthread, params);

    return *(mat*)c;
}

vec mv_multi(mat A, vec x, bool mthread, size_t params) {

    if (A.m != x.n) {
	      LOG_ERROR("Incompatible sizes; matrix size: %dx%d, vector size: %d", A.n, A.m, x.n);
        exit(1);
    }

    void* c = naive(A, (void*)&x, MATxVEC, mthread, params);

    return *(vec*)c;
}
