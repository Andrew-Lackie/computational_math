#include "matrices.h"

mat mat_multi(mat A, mat B, bool mthread, size_t params) {

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %f, l: %f and l: %f, m: %f", A.n, B.m, A.m, B.n);
        exit(1);
    }

    mat c = naive(A, B, mthread, params);

    return c;
}
