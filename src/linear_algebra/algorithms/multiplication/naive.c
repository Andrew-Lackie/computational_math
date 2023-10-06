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
        for (size_t j = 0; j < _B.m; j++) {
            for (size_t k = 0; k < _A.m; k++) {
               _C.elements[i][j] += _A.elements[i][k] * _B.elements[k][j];
            }
        }
    }

    data->thread_count++;

    return NULL;
}

mat naive(mat A, mat B, bool mthread, size_t total_threads) {

    mat C = new_matrix(A.n, B.m);

    if (!mthread) {

        for (size_t i = 0; i < A.n; i++) {
            for (size_t j = 0; j < B.m; j++) {
                for (size_t k = 0; k < B.n; k++) {
                    C.elements[i][j] += A.elements[i][k] * B.elements[k][j];
                }
            }

        }
    }
    else {
        mat* matrices = (mat*)malloc(3 * sizeof(mat));

        matrices[0] = A;
        matrices[1] = B;
        matrices[2] = C;

        thread_manager((void*) matrices, thread, NULL, A.n, total_threads);
    }

    return C;
}
