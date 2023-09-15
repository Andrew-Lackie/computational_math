#include "matrices_test.h"

void matrices() {

	mat m = mat_identity(3, 3);
	mat n = mat_zero(3, 3);

	n.elements[0][0] = 1;
	n.elements[0][1] = 3;
	n.elements[0][2] = 5;
	n.elements[1][1] = 6;
	n.elements[1][2] = 2;
	n.elements[2][2] = 9;

	printm(n);
	printf("\n");

	printm(m);
	printf("\n");

	mat multi = mat_multi(n, m);

	printm(multi);
	printf("\n");

	vec v = mat_get_row(1, n);

	printv(v);
	printf("\n");
	mat_transpose(&n);

	printm(n);
	printf("\n");

	v = mat_get_row(1, n);

	printv(v);
	printf("\n");

	bool prod = mat_is_product(m, m, n, 10);

	printf("%d", prod);
	printf("\n");

}
