#include "vectors.h"

/* vector functions */

// New vector

vec new_vector(size_t dim) {

    vec v = { .n = dim };

    void* block_v = m_allocate(dim * sizeof(f32), MEMORY_TAG_VECTOR);
    f32* block_f = (f32*) block_v;

    v.elements = block_f;

    return v;
}

void free_vector(vec* A) {
    size_t size = A->n * sizeof(f32);
    void* block = (void*) A->elements;
    m_free(block, size, MEMORY_TAG_VECTOR);
}

vec vec_va_list_construct(size_t dim, ...) {

    vec v = new_vector(dim);

    va_list list;
    va_start(list, dim);

    for (size_t i = 0; i < dim; i++) {
        v.elements[i] = va_arg(list, double);
    }

    va_end(list);

    return v;
}

vec vec_default_construct(size_t dim, f32 val) {

    vec v = new_vector(dim);

    for (size_t i = 0; i < dim; i++) {
        v.elements[i] = val;
    }

    return v;
}

vec vec_zero_construct(size_t dim) {

    vec v = vec_default_construct(dim, 0);

    return v;
}

vec vec_array_construct(size_t dim, f32 arr[]) {

    vec v = new_vector(dim);

    for (size_t i = 0; i < dim; i++) {
        v.elements[i] = arr[i];
    }

    return v;
}

void printv(vec v) {
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

char* vec_to_str(vec v) {
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

vec vec_copy(vec v) {

    vec u = new_vector(v.n);

    for (size_t i = 0; i < v.n; i++) {
        u.elements[i] = v.elements[i];
    }

    /*memcpy(&u, &v, sizeof(vec));*/

    return u;
}

void vec_fn(vec *v, f32 (*f)(f32)) {

    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] = f(v->elements[i]);
    }
}

// Equality

bool vec_equal(vec u, vec v) {

    if (u.n != v.n) {return false;}

    for (size_t i = 0; i < u.n; i++) {
        if (u.elements[i] != v.elements[i]) {
            return false;
        }
    }
    return true;
}

// Add

vec vec_add(vec u, vec v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    vec sum = new_vector(u.n);

    for (size_t i = 0; i < u.n; i++) {
        sum.elements[i] = u.elements[i] + v.elements[i];
    }
    return sum;
}

void vec_add_to(vec *v, vec u) {

    if (u.n != v->n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v->n);
        exit(1);
    }

    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] += u.elements[i];
    }
}

// Subtract

vec vec_subtract(vec u, vec v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    vec diff = new_vector(u.n);

    for (size_t i = 0; i < u.n; i++) {
        diff.elements[i] = u.elements[i] - v.elements[i];
    }
    return diff;
}

void vec_subtract_from(vec *v, vec u) {

    if (u.n != v->n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v->n);
        exit(1);
    }

    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] -= u.elements[i];
    }
}

// Multi

void vec_scalar_multiply(vec *v, f32 k) {

    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] = v->elements[i] * k;
    }
}

vec vec_multiply(vec u, vec v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    vec vector = new_vector(u.n);

    for (size_t i = 0; i < u.n; i++) {
        vector.elements[i] = u.elements[i] * v.elements[i];
    }
    return vector;
}

void vec_multiply_by(vec *v, vec u) {

    if (u.n != v->n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v->n);
        exit(1);
    }

    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] *= u.elements[i];
    }
}

// Divide

void vec_scalar_divide(vec *v, f32 k) {
    for (size_t i = 0; i < v->n; i++) {
        v->elements[i] = v->elements[i] / k;
    }
}

// Dot Product

u32 vec_dot(vec u, vec v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    u32 product = 0;


    for (size_t i = 0; i < u.n; i++) {
        product += u.elements[i] * v.elements[i];
    }
    return product;
}

// Cross Product

vec vec_cross(vec u, vec v) {

    if (u.n != v.n) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", u.n, v.n);
        exit(1);
    }

    else if (u.n == 3)  {

        vec orth = new_vector(u.n);

        orth.elements[0] = (u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1]);
        orth.elements[1] = (u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2]);
        orth.elements[2] = (u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on vectors where n > 3: %f and %f", u.n, v.n);
        exit(1);
    }
}

bool vec_orthogonal(vec u, vec v) {
    return (vec_dot(u, v) == 0) ? true : false;
}

f32 vec_magnitude_squared(vec v) {

    f32 mag_sq = 0;

    for (size_t i = 0; i < v.n; i++) {
        mag_sq += v.elements[i] * v.elements[i];
    }

    return mag_sq;
}

f32 vec_magnitude(vec v) {
    return fabs(sqrt(vec_magnitude_squared(v)));
}

void vec_normalize(vec *v) {
    f32 mag = vec_magnitude(*v);
    vec_scalar_divide(v, mag);
}

/* Real unit vectors */

// Positive
/*const vec vector_R_POS_2X_UNIT = vector(1.0f, 0.0f);*/
/*const vec vector_R_POS_2Y_UNIT = vector(0.0f, 1.0f);*/

/*const vec vector_R_POS_3X_UNIT = vector(1.0f, 0.0f, 0.0f);*/
/*const vec vector_R_POS_3Y_UNIT = vector(0.0f, 1.0f, 0.0f);*/
/*const vec vector_R_POS_3Z_UNIT = vector(0.0f, 0.0f, 1.0f);*/

/*const vec vector_R_POS_4X_UNIT = vector(1.0f, 0.0f, 0.0f, 0.0f);*/
/*const vec vector_R_POS_4Y_UNIT = vector(0.0f, 1.0f, 0.0f, 0.0f);*/
/*const vec vector_R_POS_4Z_UNIT = vector(0.0f, 0.0f, 1.0f, 0.0f);*/
/*const vec vector_R_POS_4W_UNIT = vector(0.0f, 0.0f, 0.0f, 1.0f);*/

/*// Negative*/
/*const vec vector_R_NEG_2X_UNIT = vector(-1.0f, 0.0f);*/
/*const vec vector_R_NEG_2Y_UNIT = vector(0.0f, -1.0f);*/

/*const vec vector_R_NEG_3X_UNIT = vector(-1.0f, 0.0f, 0.0f);*/
/*const vec vector_R_NEG_3Y_UNIT = vector(0.0f, -1.0f, 0.0f);*/
/*const vec vector_R_NEG_3Z_UNIT = vector(0.0f, 0.0f, -1.0f);*/

/*const vec vector_R_NEG_4X_UNIT = vector(-1.0f, 0.0f, 0.0f, 0.0f);*/
/*const vec vector_R_NEG_4Y_UNIT = vector(0.0f, -1.0f, 0.0f, 0.0f);*/
/*const vec vector_R_NEG_4Z_UNIT = vector(0.0f, 0.0f, -1.0f, 0.0f);*/
/*const vec vector_R_NEG_4W_UNIT = vector(0.0f, 0.0f, 0.0f, -1.0f);*/

/*[> Complex unit vectors <]*/

/*const vec vector_C_POS_2X_UNIT = { 2, { 1.0f * I, 0.0 }};*/
/*const vec vector_C_POS_2Y_UNIT = { 2, { 0, 1.0f * I }};*/

/*const vec vector_C_POS_3X_UNIT = { 3, { 1.0f * I, 0.0f, 0.0f }};*/
/*const vec vector_C_POS_3Y_UNIT = { 3, { 0.0f, 1.0f * I, 0.0f }};*/
/*const vec vector_C_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f * I }};*/

/*const vec vector_C_POS_4X_UNIT = { 4, { 1.0f * I, 0.0f, 0.0f, 0.0f }};*/
/*const vec vector_C_POS_4Y_UNIT = { 4, { 0.0f, 1.0f * I, 0.0f, 0.0f }};*/
/*const vec vector_C_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f * I, 0.0f }};*/
/*const vec vector_C_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f * I }};*/

/*// Negative*/
/*const vec vector_C_NEG_2X_UNIT = { 2, { -1.0f * I, 0.0 }};*/
/*const vec vector_C_NEG_2Y_UNIT = { 2, { 0, -1.0f * I }};*/

/*const vec vector_C_NEG_3X_UNIT = { 3, { -1.0f * I, 0.0f, 0.0f }};*/
/*const vec vector_C_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f * I, 0.0f }};*/
/*const vec vector_C_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f * I }};*/

/*const vec vector_C_NEG_4X_UNIT = { 4, { -1.0f * I, 0.0f, 0.0f, 0.0f }};*/
/*const vec vector_C_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f * I, 0.0f, 0.0f }};*/
/*const vec vector_C_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f * I, 0.0f }};*/
/*const vec vector_C_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f * I }};*/
