#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "../assert/logger.h"

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "MATRIX     ",
    "LINEAR_ALLC",
    "STRING     ",
    "HASHTABLE  "};

struct memory_stats {
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static struct memory_stats stats;

void initialize_memory() {
    memset(&stats, 0, sizeof(stats));
}

void* m_allocate(u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_allocate called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }
    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    void* block = malloc(size);
    memset(block, 0, size);

    return block;
}

void m_free(void* block, u64 size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_free called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    free(block);
}

void* m_copy_memory(void* dest, const void* source, u64 size) {
    return memcpy(dest, source, size);
}

void* m_set_memory(void* dest, i32 value, u64 size) {
    return memset(dest, value, size);
}

char* get_memory_usage_str() {
    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++) {
        char unit[4] = "XiB";
        f32 amount = 1.0f;
        if (stats.tagged_allocations[i] >= (f32)GIBIBYTES(1)) {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (f32)GIBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= MEBIBYTES(1)) {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (f32)MEBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= (f32)KIBIBYTES(1)) {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (f32)KIBIBYTES(1);
        }
        else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (f32)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, " %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char* out_string = strdup(buffer);
    return out_string;
}
