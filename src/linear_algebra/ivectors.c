#include <ivectors.h>

/* ivector functions */

// New ivector

vector ivector_va_list_construct(size_t dim, ...)
{

    VECTOR_INIT(v, dim);

    va_list list;
    va_start(list, dim);

    i32 element;

    for (size_t i = 0; i < dim; i++) {
        element = va_arg(list, double);
        VECTOR_SET(v, i32, i, &element);
    }

    va_end(list);

    return v;
}

vector ivector_default_construct(size_t dim, i32 val)
{

    VECTOR_INIT(v, dim);

    i32 element;

    for (size_t i = 0; i < dim; i++) {
        element = val;
        VECTOR_SET(v, i32, i, &element);
    }

    return v;
}

vector ivector_zero_construct(size_t dim)
{

    vector v = ivector_default_construct(dim, 0);

    return v;
}

vector ivector_array_construct(size_t dim, i32 arr[])
{

    VECTOR_INIT(v, dim);

    i32 elements;

    for (size_t i = 0; i < dim; i++) {
        elements = arr[i];
        VECTOR_SET(v, i32, i, &elements);
    }

    return v;
}

void printiv(vector v)
{
    printf("[ ");

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        printf("%i", VECTOR_GET(v, i32, i));

        if (i < VECTOR_TOTAL(v) - 1) {
            printf(", ");
        }
        else {
            printf(" ");
        }
    }
    printf("]\n");
}

char* ivector_to_str(vector v)
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

vector ivector_copy(vector v)
{

    VECTOR_INIT(u, VECTOR_TOTAL(v));

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        VECTOR_SET(v, i32, i, &VECTOR_GET(v, i32, i));
    }

    /*memcpy(&u, &v, sizeof(vector));*/

    return u;
}

void ivector_fn(vector *v, i32 (*f)(i32))
{

    i32 elements;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        elements = f(VECTOR_GET(*v, i32, i));
        VECTOR_SET(*v, i32, i, &elements);
    }
}

// Equality

bool ivector_equal(vector u, vector v)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {return false;}

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        if (VECTOR_GET(u, i32, i) != VECTOR_GET(v, i32, i)) {
            return false;
        }
    }
    return true;
}

// Add

vector ivector_add(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(u)) {
	      LOG_ERROR("Action undefined on ivectors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(sum, VECTOR_TOTAL(u));

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, i32, i) + VECTOR_GET(u, i32, i);
        VECTOR_SET(sum, i32, i, &element);
    }
    return sum;
}

void ivector_add_to(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on ivectors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, i32, i) + VECTOR_GET(u, i32, i);
        VECTOR_SET(*v, i32, i, &element);
    }
}

// Subtract

vector ivector_subtract(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(diff, VECTOR_TOTAL(u));

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, i32, i) - VECTOR_GET(u, i32, i);
        VECTOR_SET(diff, i32, i, &element);
    }
    return diff;
}

void ivector_subtract_from(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, i32, i) - VECTOR_GET(u, i32, i);
        VECTOR_SET(*v, i32, i, &element);
    }
}

// Multi

void ivector_scale(vector *v, i32 k)
{

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, i32, i) * k;
        VECTOR_SET(*v, i32, i, &element);
    }
}

vector ivector_multiply(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    VECTOR_INIT(multi, VECTOR_TOTAL(u));

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        element = VECTOR_GET(v, i32, i) * VECTOR_GET(u, i32, i);
        VECTOR_SET(multi, i32, i, &element);
    }
    return multi;
}

void ivector_multiply_by(vector *v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(*v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(*v));
        exit(1);
    }

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, i32, i) * VECTOR_GET(u, i32, i);
        VECTOR_SET(*v, i32, i, &element);
    }
}

// Divide

void ivector_scalar_divide(vector *v, i32 k)
{

    i32 element;

    for (i32 i = 0; i < VECTOR_TOTAL(*v); i++) {
        element = VECTOR_GET(*v, i32, i) / k;
        VECTOR_SET(*v, i32, i, &element);
    }
}

// Dot Product

u32 ivector_dot(vector v, vector u)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    u32 product = 0;

    for (i32 i = 0; i < VECTOR_TOTAL(u); i++) {
        product += VECTOR_GET(v, i32, i) * VECTOR_GET(u, i32, i);
    }
    return product;
}

// Cross Product

vector ivector_cross(vector u, vector v)
{

    if (VECTOR_TOTAL(u) != VECTOR_TOTAL(v)) {
	      LOG_ERROR("Action undefined on ivectortors of different sizes: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }

    else if (VECTOR_TOTAL(u) == 3)  {

        i32 el1;
        i32 el2;
        i32 el3;

        VECTOR_INIT(orth, VECTOR_TOTAL(u));

        el1 = VECTOR_GET(u, i32, 1) * VECTOR_GET(v, i32, 2) - VECTOR_GET(u, i32, 2) * VECTOR_GET(v, i32, 1);
        el2 = VECTOR_GET(u, i32, 2) * VECTOR_GET(v, i32, 0) - VECTOR_GET(u, i32, 0) * VECTOR_GET(v, i32, 2);
        el3 = VECTOR_GET(u, i32, 0) * VECTOR_GET(v, i32, 1) - VECTOR_GET(u, i32, 1) * VECTOR_GET(v, i32, 0);

        VECTOR_SET(orth, i32, 0 , &el1);
        VECTOR_SET(orth, i32, 1 , &el2);
        VECTOR_SET(orth, i32, 2 , &el3);

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on ivector where n > 3: %i and %i", VECTOR_TOTAL(u), VECTOR_TOTAL(v));
        exit(1);
    }
}

bool ivector_orthogonal(vector u, vector v)
{
    return (ivector_dot(u, v) == 0) ? true : false;
}

i32 ivector_magnitude_squared(vector v)
{

    i32 mag_sq = 0;

    for (i32 i = 0; i < VECTOR_TOTAL(v); i++) {
        mag_sq += VECTOR_GET(v, i32, i) * VECTOR_GET(v, i32, i);
    }

    return mag_sq;
}

i32 ivector_magnitude(vector v)
{
    return fabs(sqrt(ivector_magnitude_squared(v)));
}

void ivector_normalize(vector *v)
{
    i32 mag = ivector_magnitude(*v);
    ivector_scalar_divide(v, mag);
}
