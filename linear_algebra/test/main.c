/*#include "test.h"*/

#include "vectors_test.h"
#include "matrices_test.h"

int main() {

	initialize_memory();

	/*vectors();*/

	matrices();

	printf("%s", get_memory_usage_str());

	return 0;
}
