#include <strings.h>
#include <stdlib.h>
#include "vectors.h"
#include <complex.h>

/* Real unit vectors */

// Positive
const m_vector VECTOR_R_POS_2X_UNIT = { 2, { 1.0f, 0.0 }};
const m_vector VECTOR_R_POS_2Y_UNIT = { 2, { 0, 1.0f }};

const m_vector VECTOR_R_POS_3X_UNIT = { 3, { 1.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_POS_3Y_UNIT = { 3, { 0.0f, 1.0f, 0.0f }};
const m_vector VECTOR_R_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f }};

const m_vector VECTOR_R_POS_4X_UNIT = { 4, { 1.0f, 0.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_POS_4Y_UNIT = { 4, { 0.0f, 1.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f, 0.0f }};
const m_vector VECTOR_R_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f }};

// Negative
const m_vector VECTOR_R_NEG_2X_UNIT = { 2, { -1.0f, 0.0 }};
const m_vector VECTOR_R_NEG_2Y_UNIT = { 2, { 0, -1.0f }};

const m_vector VECTOR_R_NEG_3X_UNIT = { 3, { -1.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f, 0.0f }};
const m_vector VECTOR_R_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f }};

const m_vector VECTOR_R_NEG_4X_UNIT = { 4, { -1.0f, 0.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f, 0.0f, 0.0f }};
const m_vector VECTOR_R_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f, 0.0f }};
const m_vector VECTOR_R_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f }};

/* Complex unit vectors */

const m_vector VECTOR_C_POS_2X_UNIT = { 2, { 1.0f * I, 0.0 }};
const m_vector VECTOR_C_POS_2Y_UNIT = { 2, { 0, 1.0f * I }};

const m_vector VECTOR_C_POS_3X_UNIT = { 3, { 1.0f * I, 0.0f, 0.0f }};
const m_vector VECTOR_C_POS_3Y_UNIT = { 3, { 0.0f, 1.0f * I, 0.0f }};
const m_vector VECTOR_C_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f * I }};

const m_vector VECTOR_C_POS_4X_UNIT = { 4, { 1.0f * I, 0.0f, 0.0f, 0.0f }};
const m_vector VECTOR_C_POS_4Y_UNIT = { 4, { 0.0f, 1.0f * I, 0.0f, 0.0f }};
const m_vector VECTOR_C_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f * I, 0.0f }};
const m_vector VECTOR_C_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f * I }};

// Negative
const m_vector VECTOR_C_NEG_2X_UNIT = { 2, { -1.0f * I, 0.0 }};
const m_vector VECTOR_C_NEG_2Y_UNIT = { 2, { 0, -1.0f * I }};

const m_vector VECTOR_C_NEG_3X_UNIT = { 3, { -1.0f * I, 0.0f, 0.0f }};
const m_vector VECTOR_C_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f * I, 0.0f }};
const m_vector VECTOR_C_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f * I }};

const m_vector VECTOR_C_NEG_4X_UNIT = { 4, { -1.0f * I, 0.0f, 0.0f, 0.0f }};
const m_vector VECTOR_C_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f * I, 0.0f, 0.0f }};
const m_vector VECTOR_C_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f * I, 0.0f }};
const m_vector VECTOR_C_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f * I }};

/* vector functions */

// Equality

bool m_vector_equal(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {return false;}

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        if (u.elements[i] == v.elements[i]) {
            return true;
        }
    }
    return false;
}

// Add

m_vector m_vector_add(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }

    m_vector sum = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        sum.elements[i] = u.elements[i] + v.elements[i];
    }
    return sum;
}

// Subtract

m_vector m_vector_sub(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }

    m_vector diff = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        diff.elements[i] = u.elements[i] - v.elements[i];
    }
    return diff;
}

// Multi

m_vector m_vector_multi(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }

    m_vector product = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        product.elements[i] = u.elements[i] * v.elements[i];
    }
    return product;
}

// Dot Product

u32 m_vector_dot(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }

    u32 product;

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        product += u.elements[i] * v.elements[i];
    }
    return product;
}

// Cross Product

m_vector m_vector_x(m_vector u, m_vector v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_ERROR("Action undefined on vectors of different sizes: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }

    else if (ARRAY_SIZE(u) == 3)  {
        m_vector orth = { .n = 3 };

        orth.elements[0] = (u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1]);
        orth.elements[1] = (u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2]);
        orth.elements[3] = (u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);

        return orth;
    }

    else {
	      LOG_ERROR("Action undefined on vectors where n > 3: %f and %f", ARRAY_SIZE(u), ARRAY_SIZE(v));
        exit(1);
    }
}
