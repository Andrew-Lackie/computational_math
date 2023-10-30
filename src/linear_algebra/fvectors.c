#include <fvectors.h>

/* fvectorfunctions */

// New fvector

vector fvector_va_list_construct(size_t dim, ...) {

    VECTOR_INIT(v, dim);

    va_list list;
    va_start(list, dim);

    for (size_t i = 0; i < dim; i++) {
        f32 elements = va_arg(list, double);
        v.vector_list.elements[i] = (void*) &elements;
    }

    va_end(list);

    return v;
}

vector fvector_default_construct(size_t dim, f32 val) {

    VECTOR_INIT(v, dim);

    for (size_t i = 0; i < dim; i++) {
        f32 elements = val;
        v.vector_list.elements[i] = (void*) &elements;
    }

    return v;
}

vector fvector_zero_construct(size_t dim) {

    vector v = fvector_default_construct(dim, 0);

    return v;
}

vector fvector_array_construct(size_t dim, f32 arr[]) {

    VECTOR_INIT(v, dim);

    for (size_t i = 0; i < dim; i++) {
        f32 elements = arr[i];
        v.vector_list.elements[i] = (void*)&elements;
    }

    return v;
}

void printv(vector v) {
    printf("[ ");

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        printf("%f", *(f32*)v.vector_list.elements[i]);

        if (i < VECTOR_TOTAL(v) - 1) {
            printf(", ");
        }
        else {
            printf(" ");
        }
    }
    printf("]\n");
}

char* fvector_to_str(vector v) {
    size_t length = VECTOR_TOTAL(v) * (VECTOR_TOTAL(v) - 1) + 2;

    char* str = malloc(VECTOR_TOTAL(v) * (VECTOR_TOTAL(v) - 1) + 2);

    str[0] = '{';
    str[length] = '}';

    for (size_t i = 1; i < length; i+=2) {
        str[i] = *(char*)v.vector_list.elements[i];
        str[i+1] = ',';
    }

    return str;
}

vector fvector_copy(vector v) {

    VECTOR_INIT(u, VECTOR_TOTAL(v));

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        u.vector_list.elements[i] = v.vector_list.elements[i];
    }

    /*memcpy(&u, &v, sizeof(vector));*/

    return u;
}

void fvector_fn(vector *v, f32 (*f)(f32)) {

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        f32 elements = f(*(f32*)v->vector_list.elements[i]);
        v->vector_list.elements[i] = (void*)&elements;
    }
}

// Equality

bool fvector_equal(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {return false;}

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        if (u.vector_list.elements[i] != v.vector_list.elements[i]) {
            return false;
        }
    }
    return true;
}

// Add

vector fvector_add(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(u)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(sum, VECTOR_TOTAL(u));

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        f32 elements = *(f32*)u.vector_list.elements[i] + *(f32*)v.vector_list.elements[i];
        sum.vector_list.elements[i] = (void*)&elements;
    }
    return sum;
}

void fvector_add_to(vector *v, vector u) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements += *(f32*)u.vector_list.elements[i];
        v->vector_list.elements[i] = (void*)&elements;
    }
}

// Subtract

vector fvector_subtract(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(diff, VECTOR_TOTAL(u));

    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        elements = *(f32*)u.vector_list.elements[i] - *(f32*)v.vector_list.elements[i];
        diff.vector_list.elements[i] = (void*)&elements;
    }
    return diff;
}

void fvector_subtract_from(vector *v, vector u) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements -= *(f32*)u.vector_list.elements[i];
        v->vector_list.elements[i] = (void*)&elements;
    }
}

// Multi

void fvector_scale(vector *v, f32 k) {

    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements = *(f32*)v->vector_list.elements[i] * k;
        v->vector_list.elements[i] = (void*)&elements;
    }
}

vector fvector_multiply(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(vector, VECTOR_TOTAL(u));
    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        elements = *(f32*)u.vector_list.elements[i] * *(f32*)v.vector_list.elements[i];
        vector.vector_list.elements[i] = (void*)&elements;
    }
    return vector;
}

void fvector_multiply_by(vector *v, vector u) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements *= *(f32*)u.vector_list.elements[i];
        v->vector_list.elements[i] = (void*)&elements;
    }
}

// Divide

void fvector_scalar_divide(vector *v, f32 k) {
    f32 elements;
    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements = *(f32*)v->vector_list.elements[i] / k;
        v->vector_list.elements[i] = (void*)&elements;
    }
}

// Dot Product

u32 fvector_dot(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    u32 product = 0;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        product += *(f32*)u.vector_list.elements[i] * *(f32*)v.vector_list.elements[i];
    }
    return product;
}

// Cross Product

vector fvector_cross(vector u, vector v) {

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    else if (VECTOR_TOTAL(u) == 3)  {

        f32 el1;
        f32 el2;
        f32 el3;

        VECTOR_INIT(orth, VECTOR_TOTAL(u));

        el1 = (*(f32*)u.vector_list.elements[1] * *(f32*)v.vector_list.elements[2] - *(f32*)u.vector_list.elements[2] * *(f32*)v.vector_list.elements[1]);
        el2 = (*(f32*)u.vector_list.elements[2] * *(f32*)v.vector_list.elements[0] - *(f32*)u.vector_list.elements[0] * *(f32*)v.vector_list.elements[2]);
        el3 = (*(f32*)u.vector_list.elements[0] * *(f32*)v.vector_list.elements[1] - *(f32*)u.vector_list.elements[1] * *(f32*)v.vector_list.elements[0]);

        orth.vector_list.elements[0] = (void*)&el1;
        orth.vector_list.elements[1] = (void*)&el2;
        orth.vector_list.elements[2] = (void*)&el3;

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on fvectortors where n > 3: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }
}

bool fvector_orthogonal(vector u, vector v) {
    return (fvector_dot(u, v) == 0) ? true : false;
}

f32 fvector_magnitude_squared(vector v) {

    f32 mag_sq = 0;

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        mag_sq += *(f32*)v.vector_list.elements[i] * *(f32*)v.vector_list.elements[i];
    }

    return mag_sq;
}

f32 fvector_magnitude(vector v) {
    return fabs(sqrt(fvector_magnitude_squared(v)));
}

void fvector_normalize(vector *v) {
    f32 mag = fvector_magnitude(*v);
    fvector_scalar_divide(v, mag);
}
