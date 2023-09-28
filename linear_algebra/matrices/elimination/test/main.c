#include "../gaussj.h"

int main() {

    mat a = mat_zero(2,2);
    mat b = mat_zero(2,2);

    a.elements[0][0] = 3.0f;
    a.elements[0][1] = 4.0f;
    a.elements[1][0] = 4.0f;
    a.elements[1][1] = -2.0f;

    b.elements[0][0] = 5.0f;
    b.elements[1][0] = 7.0f;

    mat a_inv = mat_copy(a);
    mat b_sol = mat_copy(b);

    printf("\n");

    gaussj(&a_inv,&b_sol);


    printm(a);
    printm(b);

    printf("\n");

    printm(a_inv);
    printm(b_sol);

    printf("\n");

    mat multi = mat_multi(a_inv, a);

    printm(multi);

}
