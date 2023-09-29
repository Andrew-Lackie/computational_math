#include "matrices.h"

// Multi

struct thread_data {
    mat *matrices;
    size_t total_threads;
    size_t thread_count;
    size_t row;
    size_t rows_per_thread;
    size_t rows_per_last_thread;
};

static void* thread(void* arg) {

    struct thread_data *data;
    data = (struct thread_data *) arg;

    printf("Rows per thread: %lu\n", data->rows_per_thread);
    printf("Rows per last thread: %lu\n", data->rows_per_last_thread);
    printf("Thread count: %lu\n", data->thread_count);

    size_t rows_per_thread = data->total_threads == data->thread_count ? data->rows_per_last_thread : data->rows_per_thread;
    size_t curr_row = data->row;
    data->row += rows_per_thread;

    printf("Rows per thread: %lu\n", data->rows_per_thread);
    printf("Current row: %lu\n", curr_row);
    printf("curr_row + rows_per_thread: %lu\n", curr_row+rows_per_thread);

    mat* matrices = data->matrices;
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

static mat naive(mat A, mat B, bool mthread) {

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

        /*size_t MAX_THREADS = A.m;*/

        size_t cores = 10;
        size_t MAX_THREADS = cores;
        size_t total_rows = A.m;
        size_t rows_per_thread =  floor((f32) A.m / (f32) cores);
        size_t rows_per_last_thread = total_rows % rows_per_thread + rows_per_thread;

        mat* matrices = (mat*)malloc(3 * sizeof(mat));

        matrices[0] = A;
        matrices[1] = B;
        matrices[2] = C;

        struct thread_data arg;

        arg.matrices = matrices;
        arg.rows_per_thread = rows_per_thread;
        arg.rows_per_last_thread = rows_per_last_thread;
        arg.total_threads = cores - 1;
        arg.thread_count = 0;
        arg.row = 0;

        // declaring threads
        pthread_t threads[MAX_THREADS];

        // Creating four threads, each evaluating its own part
        for (size_t i = 0; i < MAX_THREADS; i++) {
            pthread_create(&threads[i], NULL, thread, (void*)&arg);
        }

        // joining and waiting for all threads to complete
        for (size_t i = 0; i < MAX_THREADS; i++)
            pthread_join(threads[i], NULL);
    }

    return C;
}

mat mat_multi(mat A, mat B, bool mthread) {

    if (A.m != B.n) {
	      LOG_ERROR("Action undefined on matrices of incompatible sizes (nxl and lxm): n: %f, l: %f and l: %f, m: %f", A.n, B.m, A.m, B.n);
        exit(1);
    }

    mat c = naive(A, B, mthread);

    return c;
}
