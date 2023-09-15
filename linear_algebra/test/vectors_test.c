#include "vectors_test.h"

f32 power(f32 x) {
	return x * x;
}

void vectors() {

	f32 arr[] = {1,3,4,6};

	vec arr_vec = vec_array_construct(4, arr);

	vec v = vec_default_construct(3, 1.0f);

	vec w = vector(1.0, 2.0, 3.0);

	vec u = vec_copy(w);

	printv(arr_vec);
	printv(w);
	printf("\n");

	vec cr = vec_cross(v, w);

	printv(cr);

	printf("%i", vec_dot(cr, v));

}
