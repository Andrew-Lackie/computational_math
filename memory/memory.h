#include "../defines.h"

/**
 * Tags to track memory allocation
 **/

typedef enum memory_tag {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_MATRIX,
    MEMORY_TAG_STRING,
    MEMORY_TAG_LINEAR_ALLOCATOR,
    MEMORY_TAG_HASHTABLE,
    MEMORY_TAG_MAX_TAGS
} memory_tag;

/**
 * Totally memory struct
 **/

typedef struct {
    u64 total_alloc_size;
} memory_system_configuration;

/**
 * Memory system initalizer
 **/

void initialize_memory();

/**
 * Allocate memory
 **/

void* m_allocate(u64 size, memory_tag tag);

/**
 * Free allocated memory
 **/

void m_free(void* block, u64 size, memory_tag tag);

/**
 * Zeroes out the provided block of memory
 **/

void* m_zero_memory(void* block, u64 size);

/**
 * Copies the source block to the destination block
 **/

void* m_copy_memory(void* dest, const void* source, u64 size);

/**
 * Initializes each component in the block to a value
 **/

void* m_set_memory(void* dest, i32 value, u64 size);

/**
 * Gets the memory usage string
 **/

char* get_memory_usage_str();
