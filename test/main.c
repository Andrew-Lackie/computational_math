#include "../const.h"
#include "../defines.h"
#include "../vectors/vectors.h"
#include "../memory/memory.h"
#include "../assert/logger.h"
#include <complex.h>

void test_macros(f32, f32);

int main() {

	initialize_memory();

	void* block = m_allocate(10, MEMORY_TAG_ARRAY);
	int val;

	for (u32 i = 0; i < 10; i++) {
		val = ((int *)block)[i];
		printf("%d\n", val);
	}

	char *log = get_memory_usage_str();

	printf("%s", log);

	LOG_ERROR("HELLO");

	f32 x = -3.0f;
	f32 y = 2.0f;

	test_macros(x, y);

	return 0;
}

void test_macros(f32 x, f32 y) {

	f32 max;
	f32 min;
	f32 abs;

	max = MAX(x,y);
	min = MIN(x,y);
	abs = ABS(x);

	printf("MAX: %f\nMIN: %f\nABS: %f\n", max, min, abs);

}
