#include "../const.h"
#include "../defines.h"
#include "../vectors/vectors.h"
#include "../memory/memory.h"
#include "../assert/logger.h"
#include "../assert/asserts.h"
#include <complex.h>

void test_macros(f32, f32);

int main() {

	initialize_memory();

	/*void *block = m_allocate(4, MEMORY_TAG_ARRAY);*/
	void *block_aligned = m_allocate_aligned(16, MEMORY_TAG_ARRAY, 4);
	int val;

	// Test memory allocator

 /* printf("[");*/
	/*for (u32 i = 0; i < 4; i++) {*/
		/*val = ((f64 *)block)[i];*/
		/*printf("%d\n", val);*/
	/*}*/
	/*printf("]");*/
	/*printf("\n");*/

	printf("[");
	for (u32 i = 0; i < 4; i++) {
		val = ((f64 *)block_aligned)[i];
		printf("%d\n", val);
	}
	printf("]");
	printf("\n");

	// Test memory alignment

	// Test Min and Max macros

 /* f32 x = -3.0f;*/
	/*f32 y = 2.0f;*/
	/*f32 max = MAX(x,y);*/
	/*f32 min = MIN(x,y);*/
	/*f32 abs = ABS(x);*/

	/*printf("MAX: %f\nMIN: %f\nABS: %f\n", max, min, abs);*/
	/*printf("\n");*/

	/*// Test NUMARGS from vector.h*/

	/*printf("NUMARGS: %lu\n", NUMARGS(int, 2, 3, 4, 5, 6));*/
	/*printf("\n");*/

	/*// Test vector macro*/

	/*m_vector v = vector(2.0f, 3.0f, 4.0f);*/
	/*m_vector u = vector(1.0f, 2.0f, 3.0f);*/

	/*LOG_DEBUG("Length of v is %d and length of u is %d. v[0] = %f and u[0] = %f", v.n, u.n, v.elements[0], u.elements[0]);*/

	/*printf("\n");*/

	/*u32 dot = m_vector_dot(v, u);*/
	/*bool equal = m_vector_equal(v, u);*/
	/*m_vector multi = m_vector_multi(v, u);*/
	/*m_vector add = m_vector_add(v, u);*/
	/*m_vector sub = m_vector_sub(v, u);*/

	/*printf("v: ");*/
	/*print_vec(v);*/
	/*printf("\n");*/
	/*printf("u: ");*/
	/*print_vec(u);*/
	/*printf("\n");*/
	/*printf("multi (u * v): ");*/
	/*print_vec(multi);*/
	/*printf("\n");*/
	/*printf("add (u + v): ");*/
	/*print_vec(add);*/
	/*printf("\n");*/
	/*printf("w (u - v): ");*/
	/*print_vec(sub);*/
	/*printf("\n");*/
	/*printf("equal: %b", equal);*/
	/*printf("\n");*/
	/*printf("dot: %u\n", dot);*/
	/*printf("\n");*/

	/*// Test vectors for complex numbers*/

	/*m_vector z1 = vector_c(3 + 2.0 * I, 3.0*I + 1, 1.0);*/
	/*m_vector z2 = vector_c(5 + 1.0 * I, 2.0*I + 0, 1.0);*/

	/*printf("Starting values: Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1.elements[0]), cimag(z1.elements[0]), creal(z2.elements[0]), cimag(z2.elements[0]));*/

	/*// Initialize vectors*/

	/*[>printf("\n");<]*/
	/*[>print_vec(VECTOR_R_POS_2X_UNIT);<]*/
	/*[>printf("\n");<]*/

	/*// Test logger*/

	LOG_INFO(get_memory_usage_str());
	/*printf("\n");*/

	/*// Test assert*/

	/*M_ASSERT(1 == 0);*/
	/*printf("\n");*/

	return 0;
}

void test_macros(f32 x, f32 y) {


}
