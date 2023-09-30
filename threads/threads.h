#ifndef _THREADS_H
#define _THREADS_H

#include "../defines.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct thread_data {
    void *data;
    size_t total_threads;
    size_t thread_count;
    size_t task;
    size_t tasks_per_thread;
    size_t tasks_per_last_thread;
};

#endif
