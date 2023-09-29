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

    mat multi = mat_multi(a_inv, a, false);

    size_t row = 1500;
    size_t col = 1500;

    mat matA = new_matrix(row, col);
    mat matB = new_matrix(row, col);

    // MATRIX MULTIPLICATION TEST

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            matA.elements[i][j] = rand() % 10;
            matB.elements[i][j] = rand() % 10;
        }
    }

    // Multi threading

    clock_t t1;
    t1 = clock();
    mat matC = mat_multi(matA, matB, true);
    t1 = clock() - t1;

    double time_taken_mthread = ((double) t1) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute multi threaded multiplication \n", time_taken_mthread);

    clock_t t2;
    t2 = clock();
    mat matD = mat_multi(matA, matB, false);
    t2 = clock() - t2;

    double time_taken_normal = ((double) t2) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute single thread multiplication \n", time_taken_normal);

    return 0;
}
