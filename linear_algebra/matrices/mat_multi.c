#include "matrices.h"

// Multi

static void* thread(void* arg) {

    struct thread_data *data;
    data = (struct thread_data *) arg;

    size_t rows_per_thread = data->total_threads == data->thread_count ? data->tasks_per_last_thread : data->tasks_per_thread;
    size_t curr_row = data->task;
    data->task += rows_per_thread;

    mat* matrices = data->data;
    mat _A = matrices[0];
    mat _B = matrices[1];
    mat _C = matrices[2];


    for (size_t i = curr_row; i < curr_row + rows_per_thread; i++) {
        for (size_t j = 0; j < _A.n; j++) {
            for (size_t k = 0; k < _A.m; k++) {
               _C.elements[i][j] += _A.elements[i][k] * _B.elements[k][j];
            }
        }
    }

    data->thread_count++;

    return NULL;
}

static mat naive(mat A, mat B, bool mthread, bool custom_params, size_t thread_count) {

    mat C = new_matrix(A.n, B.m);

    if (!mthread) {

        for (size_t i = 0; i < A.n; i++) {
            for (size_t j = 0; j < B.m; j++) {
                C.elements[i][j] = 0;

                for (size_t k = 0; k < B.n; k++) {
                    C.elements[i][j] += A.elements[i][k] * B.elements[k][j];
                }
            }

        }
    }
    else {


        size_t cores = 12;
        size_t ROW_COUNT = A.m;
        size_t TASK_COUNT = ROW_COUNT;
        size_t MAX_THREADS = cores;

        size_t THREAD_COUNT;

        if (ROW_COUNT < 1000) {
            LOG_WARN("Multithreading is inefficient for computations on smaller matrices; use the multithreading flag for matrices larger than n = m = 1000.");
        }

        if (custom_params) {

            if (thread_count == 0) {
                LOG_WARN("Custom params set to true but thread_count set to 0; reverting to default params.");
            }
            else {
                MAX_THREADS = cores;
                TASK_COUNT = thread_count;

                if (TASK_COUNT > ROW_COUNT) {
                    LOG_WARN("Specified threads are larger than maximum; reverting to default params.");
                }

                if (!(TASK_COUNT < MAX_THREADS)) {
                    LOG_INFO("Creating more threads than cores; this may be inefficient.");
                }
                else {
                    LOG_INFO("Creating less threads than cores; this may be inefficient.");
                }
            }
        }

        if (TASK_COUNT < MAX_THREADS) {
            THREAD_COUNT = TASK_COUNT;
        }
        else {
            THREAD_COUNT = MAX_THREADS;
        }

        size_t total_rows = A.m;
        size_t rows_per_thread =  floor((f32) A.m / (f32) THREAD_COUNT);
        size_t rows_per_last_thread = total_rows % rows_per_thread + rows_per_thread;

        mat* matrices = (mat*)malloc(3 * sizeof(mat));

        matrices[0] = A;
        matrices[1] = B;
        matrices[2] = C;

        struct thread_data arg;

        arg.data = matrices;
        arg.tasks_per_thread = rows_per_thread;
        arg.tasks_per_last_thread = rows_per_last_thread;
        arg.total_threads = THREAD_COUNT - 1;
        arg.thread_count = 0;
        arg.task = 0;

        // declaring threads

        pthread_t threads[THREAD_COUNT];

        // Creating four threads, each evaluating its own part
        for (size_t i = 0; i < THREAD_COUNT; i++) {
            pthread_create(&threads[i], NULL, thread, (void*)&arg);
        }

        // joining and waiting for all threads to complete
        for (size_t i = 0; i < THREAD_COUNT; i++)
            pthread_join(threads[i], NULL);
    }

    return C;
}

mat mat_multi(mat A, mat B, bool mthread, bool custom_params, size_t params) {

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %f, l: %f and l: %f, m: %f", A.n, B.m, A.m, B.n);
        exit(1);
    }

    mat c = naive(A, B, mthread, custom_params, params);

    return c;
}
