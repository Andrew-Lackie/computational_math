#include "../gaussj.h"
#include <time.h>

int main() {

    mat a = mat_zero(3,3);
    mat b = mat_zero(3,3);

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

    mat a_inv = mat_copy(a);
    mat b_sol = mat_copy(b);

    gaussj(&a_inv,&b_sol);

    /*mat multi = mat_multi(a_inv, a, true);*/

    size_t rowA = 1000;
    size_t colA = 2500;

    size_t rowB = 2500;
    size_t colB = 1300;

    mat matA = new_matrix(rowA, colA);
    mat matB = new_matrix(rowB, colB);


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

    // Multi threading

    clock_t t1;
    t1 = clock();
    mat matC = mat_multi(matA, matB, true, 12);
    t1 = clock() - t1;

    /*printm(matC);*/

    double time_taken_mthread = ((double) t1) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute multi threaded multiplication \n", time_taken_mthread);

    clock_t t2;
    t2 = clock();
    mat matD = mat_multi(matA, matB, false, 3);
    t2 = clock() - t2;

    /*printm(matD);*/

    double time_taken_normal = ((double) t2) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute single thread multiplication \n", time_taken_normal);

    return 0;
}
