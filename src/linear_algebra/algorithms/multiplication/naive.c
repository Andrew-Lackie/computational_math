#include <matrices.h>

// Multi

static void* thread(void* arg) {

    struct thread_data *data;
    data = (struct thread_data *) arg;
    size_t rows_per_thread = data->total_threads == data->thread_count ? data->tasks_per_last_thread : data->tasks_per_thread;
    size_t curr_row = data->task;
    data->task += rows_per_thread;

    struct data* payload = data->data;
    mat A = payload->A;

    if (payload->type == MATxMAT) {


        mat B = payload->B;
        mat C = payload->C;

        for (size_t i = curr_row; i < curr_row + rows_per_thread; i++) {
            for (size_t j = 0; j < B.m; j++) {
                for (size_t k = 0; k < A.m; k++) {
                   C.elements[i][j] += A.elements[i][k] * B.elements[k][j];
                }
            }
        }

        data->thread_count++;
    }
    else if (payload->type == MATxVEC) {

        vec x = payload->x;
        vec b = payload->b;


        for (size_t i = curr_row; i < curr_row + rows_per_thread; i++) {
            for (size_t j = 0; j < A.m; j++) {
               b.elements[i] += A.elements[i][j] * x.elements[j];
            }
        }

        data->thread_count++;
    }



    return NULL;
}

void* naive(mat A, void* arg, enum multi_t type, bool mthread, size_t total_threads) {

    void* ret;

    if (type == MATxMAT) {
        mat* B = (mat*) arg;
        mat C = new_matrix(A.n, B->m);

        if (!mthread) {

            for (size_t i = 0; i < A.n; i++) {
                for (size_t j = 0; j < B->m; j++) {
                    for (size_t k = 0; k < B->n; k++) {
                        C.elements[i][j] += A.elements[i][k] * B->elements[k][j];
                    }
                }

            }
            ret = (void*)&C;
        }
        else {
            struct data* payload = (struct data*)malloc(3 * sizeof(struct data));

            payload->A = A;
            payload->B = *B;
            payload->C = C;
            payload->type = MATxMAT;

            thread_manager((void*) payload, thread, NULL, A.n, total_threads);

            ret = (void*)&C;
        }
        return ret;
    }
    else if (type == MATxVEC) {
        vec* x = (vec*) arg;
        vec b = new_vector(x->n);

        if (!mthread) {
            for (size_t i = 0; i < x->n; i++) {
                for (size_t j = 0; j < x->n; j++) {
                    b.elements[i] += A.elements[i][j] * x->elements[j];
                }
            }
            ret = (void*)&b;
        }
        else {
            struct data* payload = (struct data*)malloc(sizeof(struct data));

            payload->A = A;
            payload->x = *x;
            payload->b = b;
            payload->type = MATxVEC;

            thread_manager((void*) payload, thread, NULL, x->n, total_threads);

            ret = (void*)&b;
        }

        return ret;
    }
    return NULL;
}
