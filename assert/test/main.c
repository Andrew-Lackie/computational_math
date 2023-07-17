#include "../logger.h"

int main() {

	LOG_FATAL("A test message: %f", 3.14f);
	LOG_ERROR("A test message: %f", 3.14f);
	LOG_WARN("A test message: %f", 3.14f);
	LOG_TRACE("A test message: %f", 3.14f);

	return 0;
}
