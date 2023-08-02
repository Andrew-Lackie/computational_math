#include "test.h"

f32 double_el(f32 num);

/* vector creation */

bool test_vector(size_t dim, f32 *arr, ...) {
	return true;
}

bool test_vector_n(size_t dim, f32 *arr, f32 *farr) {

	bool status = true;
	char buffer[1000];

	m_vector vec = vector_n(dim, arr);

	for (size_t i = 0; i < dim; i++) {
		if (vec.elements[i] != farr[i]) {
			status = false;
		}
	}

	i32 length;

	#define P(x) vec.elements[x]

	if (status == false) {
		switch (dim) {
			case 1: snprintf(buffer, sizeof(buffer), "given array {%.2f} and computed array {%.2f} are equal.\n", farr[0], P(0)); break;
			case 2: snprintf(buffer, sizeof(buffer), "given array {%.2f, %.2f} and computed array {%.2f, %.2f} are equal.\n", farr[0], P(0), P(1)); break;
			case 3: snprintf(buffer, sizeof(buffer), "given array {%.2f, %.2f, %.2f} and computed array {%.2f, %.2f, %.2f} are NOT equal.\n", farr[0], farr[1], farr[2], P(0), P(1), P(2)); break;
			case 4: snprintf(buffer, sizeof(buffer), "given array {%.2f, %.2f, %.2f, %.2f} and computed array {%.2f, %.2f, %.2f, %.2f} are NOT equal.\n", farr[0], farr[1], farr[2], farr[3], P(0), P(1), P(2), P(3)); break;
			default: M_ASSERT_MSG(status, "array too large to test."); return status;
		}
	}

	#undef P

	M_ASSERT_MSG(status, buffer);

	return status;
}

/*bool test_vector_f(size_t dim, f32 *arr, f32 (*f)(f32), f32 *farr);*/

/*[> vector operations <]*/

/*// Equality*/

/*bool test_m_vector_equal(m_vector, m_vector, m_vector);*/

/*// Add*/

/*bool test_m_vector_add(m_vector, m_vector, m_vector);*/

/*// Subtract*/

/*bool test_m_vector_sub(m_vector, m_vector, m_vector);*/

/*// Multi*/

/*bool test_m_vector_multi(m_vector, m_vector, m_vector);*/

/*// Dot Product*/

/*bool test_m_vector_dot(m_vector, m_vector, f32);*/

/*// Cross Product*/

/*bool test_m_vector_x(m_vector, m_vector, m_vector);*/