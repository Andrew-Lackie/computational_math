#include <gaussj.h>

void gaussj_dcmp(matrix *a, matrix *b) {
    vector indxc, indxr, ipiv;
    size_t i, icol, irow, j, k, l, ll;
    f32 big, dum, pivinv, temp;

    size_t n = a->n;
    size_t m = a->m;

    /*The integer arrays ipiv, indxr, and indxc are*/
    indxc = fvector_zero_construct(n);
    indxr = fvector_zero_construct(n);

    /*used for bookkeeping on the pivoting.*/
    ipiv = fvector_zero_construct(n);

    for (i = 0; i < n; i++) {
        /*This is the main loop over the columns to be*/
        big = 0.0;
        /*reduced.*/
        for (j = 0; j < n; j++) {
        /*This is the outer loop of the search for a pivot*/
            if (*(i32*)ipiv.vector_list.elements[j] != 1) {
            /*element.*/
                for (k = 0; k < n; k++) {
                    if (*(i32*)ipiv.vector_list.elements[k] == 0) {
                        if (fabs(a->elements[j][k]) >= big) {
                            big = fabs(a->elements[j][k]);
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (*(f32*)ipiv.vector_list.elements[k] > 1) {
	                      LOG_ERROR("gaussj: Singular Matrix-1");
                    }
                }
            }
        }
        ++(*(i32*)ipiv.vector_list.elements[icol]);

        /*if (irow != icol) {*/
            /*for (l = 0; l < n; l++) {*/
                /*SWAP(a->elements[irow][l],a->elements[icol][l])*/
            /*}*/
            /*for (l = 0; l < m; l++) {*/
                /*SWAP(b->elements[irow][l],b->elements[icol][l])*/
            /*}*/
        /*}*/

        indxr.vector_list.elements[i] = (void*)&irow;

        /*We are now ready to divide the pivot row by the*/
        indxc.vector_list.elements[i] = (void*)&icol;
/*pivot element, located at irow and icol.*/
        if (a->elements[icol][icol]  ==  0.0)
            LOG_ERROR("gaussj: Singular Matrix-1");

        pivinv = 1.0 / a->elements[icol][icol];
        a->elements[icol][icol] = 1.0;

        for (l = 0; l < n; l++) a->elements[icol][l] *= pivinv;
        for (l = 0; l < m; l++) b->elements[icol][l] *= pivinv;

        for (ll = 0; ll < n; ll++)
        /*Next, we reduce the rows...*/
            if (ll != icol) {

                /*...except for the pivot one, of course.*/
                dum = a->elements[ll][icol];

                a->elements[ll][icol] = 0.0;

                for (l = 0; l < n; l++) {
                    a->elements[ll][l] -= a->elements[icol][l]*dum;
                }
                for (l = 0; l < m; l++) {
                    b->elements[ll][l] -= b->elements[icol][l]*dum;
                }
            }
    }

    for (l = n; l > 0; l--) {
        if (indxr.vector_list.elements[l] != indxc.vector_list.elements[l]) {
            for (k = 0; k < n; k++) {
                SWAP(a->elements[k][*(i32*) indxr.vector_list.elements[l]], a->elements[k][*(i32*) indxc.vector_list.elements[l]]);
            }
        }
    }

    vector_free(&ipiv);
    vector_free(&indxr);
    vector_free(&indxc);
}
