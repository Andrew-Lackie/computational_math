#include "const.h"
#include "defines.h"
#include <vectors.h>
#include <fvectors.h>
#include "matrices.h"
#include "gaussj.h"
#include "lu.h"
#include "memory.h"
#include "logger.h"
#include "asserts.h"
#include <complex.h>

int main() {

    printf("HELOLO");

		matrix a = matrix_zero(3,3);
    matrix b = matrix_zero(3,3);

    vector x = fvector_default_construct(3, 3.0);

    a.elements[0][0] = 1.0f;
    a.elements[0][1] = -3.0f;
    a.elements[0][2] = 4.0f;
    a.elements[1][0] = 2.0f;
    a.elements[1][1] = -5.0f;
    a.elements[1][2] = 6.0f;
    a.elements[2][0] = -3.0f;
    a.elements[2][1] = 3.0f;
    a.elements[2][2] = 4.0f;

    b.elements[0][0] = 3.0f;
    b.elements[1][0] = 6.0f;
    b.elements[2][0] = 6.0f;

    matrix a_inv = matrix_copy(a);
    matrix b_sol = matrix_copy(b);

    matrix lu = matrix_copy(a);

    gaussj_dcmp(&a_inv,&b_sol);

    /*printm(b_sol);*/

    f32 d;
    vector indx = fvector_zero_construct(lu.n);

    vector zero_sol = fvector_zero_construct(lu.n);

    lu_dcmp(&lu, &indx, &d);
    lubskb(&lu, &indx, zero_sol);

    printv(indx);
    printm(lu);
    printf("d: %f\n", d);

    /*mat multi = mm_multi(a_inv, a, true);*/

    size_t rowA = 1000;
    size_t colA = 2500;

    size_t rowB = 2500;
    size_t colB = 1300;

    matrix matA = new_matrix(rowA, colA);
    matrix matB = new_matrix(rowB, colB);


    // MATRIX MULTIPLICATION TEST

    for (size_t i = 0; i < rowA; i++) {
        for (size_t j = 0; j < colA; j++) {
            matA.elements[i][j] = rand() % 10;
        }
    }

    for (size_t i = 0; i < rowB; i++) {
        for (size_t j = 0; j < colB; j++) {
            matB.elements[i][j] = rand() % 10;
        }
    }

    /*printm(matA);*/
    /*printf("\n");*/
    /*printm(matB);*/
    /*printf("\n");*/

    printm(a);
    printv(x);

    vector vecC = mv_multi(a, x, true, 3);

    printv(vecC);

    // Multi threading

    clock_t t1;
    t1 = clock();
    matrix matC = mm_multi(matA, matB, true, 12);
    t1 = clock() - t1;

    /*printm(matC);*/

    double time_taken_mthread = ((double) t1) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute multi threaded multiplication \n", time_taken_mthread);

    clock_t t2;
    t2 = clock();
    matrix matD = mm_multi(matA, matB, false, 3);
    t2 = clock() - t2;

    /*printm(matD);*/

    double time_taken_normal = ((double) t2) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute single thread multiplication \n", time_taken_normal);

		return 0;
}
