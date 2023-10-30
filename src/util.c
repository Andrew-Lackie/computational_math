#include <util.h>

f32 m_sqrt(f32 num) {
	 i32 i;
	 f32 x, y;
	 x = num* 0.5f;
	 y = num;
	 i  = * (i32*) &y; 						// evil floating point bit level hacking
	 i  = 0x5f3759df - (i >> 1);  // what the fuck?
	 y  = * (f32 * ) &i;
	 y  = y * (1.5f - (x * y * y ));
	 y  = y * (1.5f - (x * y * y ));
	 return num* y;
}

i32 randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {

    assert (n <= RAND_MAX);

    i32 end = RAND_MAX / n; // truncate skew
    assert (end > 0);
    end *= n;
    i32 r;
    while ((r = rand()) >= end);

    return r % n;
  }
}
