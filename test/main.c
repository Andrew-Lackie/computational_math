#include "../const.h"
#include "../defines.h"
#include "../vectors/vectors.h"
#include <complex.h>

void test_macros(f32, f32);

int main() {

	double complex c = 2.0*I;
	double complex d = 2.0*_Complex_I;

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
