#include "test.h"

int main() {

	initialize_memory();

	f32 arr[3] = {1,2,3};

	test_vector_n(3, arr, arr);

	return 0;
}

f32 double_el(f32 num) {
		return num * 2.0;
}
