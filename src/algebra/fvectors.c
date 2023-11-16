#include <fvectors.h>

/* fvectorfunctions */

// New fvector

vector fvector_va_list_construct(size_t dim, ...)
{

    VECTOR_INIT(v, dim);

    va_list list;
    va_start(list, dim);

    f32 elements;

    for (size_t i = 0; i < dim; i++) {
        elements = va_arg(list, double);
        VECTOR_SET(v, f32, i, &elements);
    }

    va_end(list);

    return v;
}

vector fvector_default_construct(size_t dim, f32 val)
{

    VECTOR_INIT(v, dim);

    f32 element;

    for (size_t i = 0; i < dim; i++) {
        element = val;
        VECTOR_SET(v, f32, i, &element);
    }

    return v;
}

vector fvector_zero_construct(size_t dim)
{

    vector v = fvector_default_construct(dim, 0.0f);

    return v;
}

vector fvector_array_construct(size_t dim, f32 arr[])
{

    VECTOR_INIT(v, dim);

    f32 element;

    for (size_t i = 0; i < dim; i++) {
        element = arr[i];
        VECTOR_SET(v, f32, i, &element);
    }

    return v;
}

void printfv(vector v)
{
    printf("[ ");

    for (f32 i = 0; i < VECTOR_TOTAL(v); i++) {
        printf("%f", VECTOR_GET(v, f32, i));

        if (i < VECTOR_TOTAL(v) - 1) {
            printf(", ");
        }
        else {
            printf(" ");
        }
    }
    printf("]\n");
}

char* fvector_to_str(vector v)
{
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

vector fvector_copy(vector v)
{

    VECTOR_INIT(u, VECTOR_TOTAL(v));

    for (f32 i = 0; i < VECTOR_TOTAL(v); i++) {
        VECTOR_SET(v, f32, i, &VECTOR_GET(v, f32, i));
    }

    /*memcpy(&u, &v, sizeof(vector));*/

    return u;
}

void fvector_fn(vector *v, f32 (*f)(f32))
{
    f32 element;
    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = f(VECTOR_GET(*v, f32, i));
        VECTOR_SET(*v, f32, i, &element);
    }
}

// Equality

bool fvector_equal(vector u, vector v)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {return false;}

    for (f32 i = 0; i < VECTOR_TOTAL(u); i++) {
        if (VECTOR_GET(u, f32, i) != VECTOR_GET(v, f32, i)) {
            return false;
        }
    }
    return true;
}

// Add

vector fvector_add(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(u)) {
	      LOG_ERROR("Action undefined on fvectors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(sum, VECTOR_TOTAL(u));

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, f32, i) + VECTOR_GET(u, f32, i);
        VECTOR_SET(sum, f32, i, &element);
    }
    return sum;
}

void fvector_add_to(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, f32, i) + VECTOR_GET(u, f32, i);
        VECTOR_SET(*v, f32, i, &element);
    }
}

// Subtract

vector fvector_subtract(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(diff, VECTOR_TOTAL(u));

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, f32, i) - VECTOR_GET(u, f32, i);
        VECTOR_SET(diff, f32, i, &element);
    }
    return diff;
}

void fvector_subtract_from(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, f32, i) - VECTOR_GET(u, f32, i);
        VECTOR_SET(*v, f32, i, &element);
    }
}

// Multi

void fvector_scale(vector *v, f32 k)
{

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, f32, i) * k;
        VECTOR_SET(*v, f32, i, &element);
    }
}

vector fvector_multiply(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(multi, VECTOR_TOTAL(u));

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, f32, i) * VECTOR_GET(u, f32, i);
        VECTOR_SET(multi, f32, i, &element);
    }
    return multi;
}

void fvector_multiply_by(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, f32, i) * VECTOR_GET(u, f32, i);
        VECTOR_SET(*v, f32, i, &element);
    }
}

// Divide

void fvector_scalar_divide(vector *v, f32 k)
{

    f32 element;

    for (f32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, f32, i) / k;
        VECTOR_SET(*v, f32, i, &element);
    }
}

// Dot Product

u32 fvector_dot(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    u32 product = 0;

    for (f32 i = 0; i < VECTOR_TOTAL(u); i++) {
        product += VECTOR_GET(v, f32, i) * VECTOR_GET(u, f32, i);
    }
    return product;
}

// Cross Product

vector fvector_cross(vector u, vector v)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on fvectortors of different sizes: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    else if (VECTOR_TOTAL(u) == 3)  {

        f32 el1;
        f32 el2;
        f32 el3;

        VECTOR_INIT(orth, VECTOR_TOTAL(u));

        el1 = VECTOR_GET(u, f32, 1) * VECTOR_GET(v, f32, 2) - VECTOR_GET(u, f32, 2) * VECTOR_GET(v, f32, 1);
        el2 = VECTOR_GET(u, f32, 2) * VECTOR_GET(v, f32, 0) - VECTOR_GET(u, f32, 0) * VECTOR_GET(v, f32, 2);
        el3 = VECTOR_GET(u, f32, 0) * VECTOR_GET(v, f32, 1) - VECTOR_GET(u, f32, 1) * VECTOR_GET(v, f32, 0);

        VECTOR_SET(orth, f32, 0 , &el1);
        VECTOR_SET(orth, f32, 1 , &el2);
        VECTOR_SET(orth, f32, 2 , &el3);

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on fvector where n > 3: %f and %f", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }
}

bool fvector_orthogonal(vector u, vector v)
{
    return (fvector_dot(u, v) == 0) ? true : false;
}

f32 fvector_magnitude_squared(vector v)
{

    f32 mag_sq = 0;

    for (f32 i = 0; i < VECTOR_TOTAL(v); i++) {
        mag_sq += VECTOR_GET(v, f32, i) * VECTOR_GET(v, f32, i);
    }

    return mag_sq;
}

f32 fvector_magnitude(vector v)
{
    return fabs(sqrt(fvector_magnitude_squared(v)));
}

void fvector_normalize(vector *v)
{
    f32 mag = fvector_magnitude(*v);
    fvector_scalar_divide(v, mag);
}
