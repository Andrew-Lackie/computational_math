#include <matrices.h>

// Multi

static void* thread(void* arg)
{

    struct thread_data *data;
    data = (struct thread_data *) arg;
    size_t rows_per_thread = data->total_threads == data->thread_count ? data->tasks_per_last_thread : data->tasks_per_thread;
    size_t curr_row = data->task;
    data->task += rows_per_thread;

    struct data* payload = data->data;
    matrix A = payload->A;

    if (payload->type == MATxMAT) {


        matrix B = payload->B;
        matrix C = payload->C;

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

        vector x = payload->x;
        vector b = payload->b;

        f32 elements;

        for (size_t i = curr_row; i < curr_row + rows_per_thread; i++) {
            for (size_t j = 0; j < A.m; j++) {
                elements += A.elements[i][j] * *(f32*)x.vector_list.elements[j];
                b.vector_list.elements[i] = (void*)&elements;
            }
        }

        data->thread_count++;
    }



    return NULL;
}

void* naive(matrix A, void* arg, enum multi_t type, bool mthread, size_t total_threads)
{

    void* ret;

    if (type == MATxMAT) {
        matrix* B = (matrix*) arg;
        matrix C = new_matrix(A.n, B->m);

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
        vector* x = (vector*) arg;
        VECTOR_INIT(b, VECTOR_TOTAL(*x));

        f32 elements;

        if (!mthread) {
            for (i32 i = 0; i < VECTOR_TOTAL(*x); i++) {
                for (i32 j = 0; j < VECTOR_TOTAL(*x); j++) {
                    elements += A.elements[i][j] * *(f32*)x->vector_list.elements[j];
                    b.vector_list.elements[i] = (void*)&elements;
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

            thread_manager((void*) payload, thread, NULL, VECTOR_TOTAL(*x), total_threads);

            ret = (void*)&b;
        }

        return ret;
    }
    return NULL;
}
