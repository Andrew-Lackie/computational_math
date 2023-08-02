#include <strings.h>
#include <stdlib.h>
#include "vectors.h"
#include <stdarg.h>
#include "../memory/memory.h"
#include <complex.h>

/* vector functions */

// New vector

m_vector new_vector(size_t dim, ...) {

    m_vector vec = { .n = dim };

    void* block_v = m_allocate(dim * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    vec.elements = block_f;

    va_list list;
    va_start(list, dim);

    for (size_t i = 0; i < dim; i++) {
        vec.elements[i] = va_arg(list, double);
    }

    return vec;
}

m_vector vector_n(size_t dim, f32 *arr) {

    m_vector vec = { .n = dim };

    void* block_v = m_allocate(dim * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    /*Replace the following with m_copy_memory eventually*/
    /*m_copy_memory(block_f, arr, dim);*/

    for (size_t i = 0; i < dim; i++) {
        block_f[i] = arr[i];
    }

    vec.elements = block_f;

    return vec;
}

m_vector vector_f(size_t dim, f32 *arr, f32 (*f)(f32)) {

    m_vector vec = { .n = dim };

    void* block_v = m_allocate(dim * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    /*Replace the following with m_copy_memory eventually*/
    /*m_copy_memory(block_f, arr, dim);*/

    for (size_t i = 0; i < dim; i++) {
        block_f[i] = f(arr[i]);
    }

    vec.elements = block_f;

    return vec;
}

void print_v(m_vector v) {
    printf("[ ");

    for (size_t i = 0; i < v.n; i++) {
        printf("%f", v.elements[i]);

        if (i < v.n - 1) {
            printf(", ");
        }
        else {
            printf(" ");
        }
    }
    printf("]\n");
}

char* vector_str(m_vector v) {
    size_t length = v.n * (v.n - 1) + 2;

    char* str = malloc(v.n * (v.n - 1) + 2);

    str[0] = '{';
    str[length] = '}';

    for (size_t i = 1; i < length; i+=2) {
        str[i] = v.elements[i];
        str[i+1] = ',';
    }

    return str;
}

// Equality

bool m_vector_equal(m_vector u, m_vector v) {

    if (u.n != v.n) {return false;}

    for (size_t i = 0; i < u.n; i++) {
        if (u.elements[i] != v.elements[i]) {
            return false;
        }
    }
    return true;
}

// Add

m_vector m_vector_add(m_vector u, m_vector v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    m_vector sum = { .n = u.n };

    void* block_v = m_allocate(u.n * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    sum.elements = block_f;

    for (size_t i = 0; i < u.n; i++) {
        sum.elements[i] = u.elements[i] + v.elements[i];
    }
    return sum;
}

// Subtract

m_vector m_vector_sub(m_vector u, m_vector v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    m_vector diff = { .n = u.n };

    void* block_v = m_allocate(u.n * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    diff.elements = block_f;

    for (size_t i = 0; i < u.n; i++) {
        diff.elements[i] = u.elements[i] - v.elements[i];
    }
    return diff;
}

// Multi

m_vector m_vector_multi(m_vector u, m_vector v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    m_vector vec = { .n = u.n };

    void* block_v = m_allocate(u.n * sizeof(f32), MEMORY_TAG_ARRAY);
    f32* block_f = (f32*) block_v;

    vec.elements = block_f;

    for (size_t i = 0; i < u.n; i++) {
        vec.elements[i] = u.elements[i] * v.elements[i];
    }
    return vec;
}

// Dot Product

u32 m_vector_dot(m_vector u, m_vector v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    u32 product;


    for (size_t i = 0; i < u.n; i++) {
        product += u.elements[i] * v.elements[i];
    }
    return product;
}

// Cross Product

m_vector m_vector_x(m_vector u, m_vector v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }


    else if (u.n == 3)  {

        m_vector orth = { .n = u.n };

        void* block_v = m_allocate(u.n * sizeof(f32), MEMORY_TAG_ARRAY);
        f32* block_f = (f32*) block_v;

        orth.elements = block_f;

        orth.elements[0] = (u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1]);
        orth.elements[1] = (u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2]);
        orth.elements[3] = (u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on vectors where n > 3: %f and %f", u.n, v.n);
        exit(1);
    }
}

/* Real unit vectors */

// Positive
/*const m_vector VECTOR_R_POS_2X_UNIT = vector(1.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_2Y_UNIT = vector(0.0f, 1.0f);*/

/*const m_vector VECTOR_R_POS_3X_UNIT = vector(1.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_3Y_UNIT = vector(0.0f, 1.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_3Z_UNIT = vector(0.0f, 0.0f, 1.0f);*/

/*const m_vector VECTOR_R_POS_4X_UNIT = vector(1.0f, 0.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_4Y_UNIT = vector(0.0f, 1.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_4Z_UNIT = vector(0.0f, 0.0f, 1.0f, 0.0f);*/
/*const m_vector VECTOR_R_POS_4W_UNIT = vector(0.0f, 0.0f, 0.0f, 1.0f);*/

/*// Negative*/
/*const m_vector VECTOR_R_NEG_2X_UNIT = vector(-1.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_2Y_UNIT = vector(0.0f, -1.0f);*/

/*const m_vector VECTOR_R_NEG_3X_UNIT = vector(-1.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_3Y_UNIT = vector(0.0f, -1.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_3Z_UNIT = vector(0.0f, 0.0f, -1.0f);*/

/*const m_vector VECTOR_R_NEG_4X_UNIT = vector(-1.0f, 0.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_4Y_UNIT = vector(0.0f, -1.0f, 0.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_4Z_UNIT = vector(0.0f, 0.0f, -1.0f, 0.0f);*/
/*const m_vector VECTOR_R_NEG_4W_UNIT = vector(0.0f, 0.0f, 0.0f, -1.0f);*/

/*[> Complex unit vectors <]*/

/*const m_vector VECTOR_C_POS_2X_UNIT = { 2, { 1.0f * I, 0.0 }};*/
/*const m_vector VECTOR_C_POS_2Y_UNIT = { 2, { 0, 1.0f * I }};*/

/*const m_vector VECTOR_C_POS_3X_UNIT = { 3, { 1.0f * I, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_POS_3Y_UNIT = { 3, { 0.0f, 1.0f * I, 0.0f }};*/
/*const m_vector VECTOR_C_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f * I }};*/

/*const m_vector VECTOR_C_POS_4X_UNIT = { 4, { 1.0f * I, 0.0f, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_POS_4Y_UNIT = { 4, { 0.0f, 1.0f * I, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f * I, 0.0f }};*/
/*const m_vector VECTOR_C_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f * I }};*/

/*// Negative*/
/*const m_vector VECTOR_C_NEG_2X_UNIT = { 2, { -1.0f * I, 0.0 }};*/
/*const m_vector VECTOR_C_NEG_2Y_UNIT = { 2, { 0, -1.0f * I }};*/

/*const m_vector VECTOR_C_NEG_3X_UNIT = { 3, { -1.0f * I, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f * I, 0.0f }};*/
/*const m_vector VECTOR_C_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f * I }};*/

/*const m_vector VECTOR_C_NEG_4X_UNIT = { 4, { -1.0f * I, 0.0f, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f * I, 0.0f, 0.0f }};*/
/*const m_vector VECTOR_C_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f * I, 0.0f }};*/
/*const m_vector VECTOR_C_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f * I }};*/