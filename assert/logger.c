#include "logger.h"

// TEMPORARY
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

bool initialize_logging() {

	return true;
}

void shutdown_logging() {

}

void log_output(log_level level, const char* message, ...) {
	const char* level_string[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
	bool is_error = level < 2;


	char *out_message = (char*)calloc(sizeof(message), sizeof(typeof(message)));
	memset(out_message, 0, sizeof(out_message));

	va_list arg_ptr;
	va_start(arg_ptr, message);
	vsnprintf(out_message, sizeof(*out_message), message, arg_ptr);
	va_end(arg_ptr);

	char *out_message2 = (char*)calloc(sizeof(message), sizeof(typeof(message)));
	sprintf(out_message2, "%s%s\n", level_string[level], out_message);
	printf("%s", out_message2);

	free(out_message);
	free(out_message2);
}
