#include "lu.h"

void lu_dcmp(mat *A, vec *indx, f32 *d) {

    size_t i, imax, j, k;
    f32 big, dum, sum, temp;
    vec vv;

    size_t n = A->n;

    /* vv stores the implicit scaling of each row. */

    vv = vec_default_construct(n, 1.0f);

    *d = 1.0;

    for (i = 0; i < n; i++) {
        /* Scaling */
        big = 0.0;
        for (j = 0; j < n; j++)
            if ((temp = fabs(A->elements[i][j])) > big) big = temp;
        if (big == 0.0) LOG_ERROR("Singular matrix in routine ludcmp");
        vv.elements[i] = 1.0 / big;
    }
    for (j = 0; j < n; j++) {
    /*This is the loop over columns of Crout’s method.*/
        for (i = 0; i < j; i++) {
            sum = A->elements[i][j];
            for (k = 0; k < i; k++) sum -= A->elements[i][k] * A->elements[k][j];
            A->elements[i][j] = sum;
        }
        big = 0.0;
        /*Initialize for the search for largest pivot element.*/
        for (i = j; i < n; i++) {
            sum = A->elements[i][j];
            for (k = 0; k < j; k++)
                sum -= A->elements[i][k] * A->elements[k][j];
            A->elements[i][j] = sum;
            if ( (dum = vv.elements[i] * fabs(sum)) >= big) {
                big = dum;
                imax = i;
            }
        }
        if (j != imax) {
            for (k = 0; k < n; k++) {
                dum = A->elements[imax][k];
                A->elements[imax][k] = A->elements[j][k];
                A->elements[j][k] = dum;
            }
            *d = -(*d);
            vv.elements[imax] = vv.elements[j];
        }
        indx->elements[j] = imax;
        if (A->elements[j][j] == 0.0) A->elements[j][j] = M_EPSILON;
        if (j != n) {
            dum = 1.0 / (A->elements[j][j]);
            for (i = j + 1; i < n; i++) A->elements[i][j] *= dum;
        }
    }

    free_vector(&vv);
}

void lubskb(mat *a, vec *indx, vec b) {

    size_t i, ii = 0, ip, j;
    f32 sum;
    size_t n = a->n;

    for (i = 0; i < n; i++) {
        ip = indx->elements[i];
        sum = b.elements[ip];
        b.elements[ip] = b.elements[i];
        if (ii)
            for (j = ii; j <= i - 1; j++) sum -= a->elements[i][j] * b.elements[j];
        else if (sum) ii = i;
            b.elements[i] = sum;
    }

    for (i = n; (i32) i >= 0; i--) {
        sum = b.elements[i];
        for (j = i; j < n; j++) sum -= a->elements[i][j] * b.elements[j];
    }
}
