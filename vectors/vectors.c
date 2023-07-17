#include <strings.h>
#include <stdlib.h>
#include "vectors.h"
#include <complex.h>

const vector_n VECTOR_N_UNDEFINED = { 0, { 0.0f } };

/* Real unit vectors */

// Positive
const vector_n VECTOR_R_POS_2X_UNIT = { 2, { 1.0f, 0.0 }};
const vector_n VECTOR_R_POS_2Y_UNIT = { 2, { 0, 1.0f }};

const vector_n VECTOR_R_POS_3X_UNIT = { 3, { 1.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_POS_3Y_UNIT = { 3, { 0.0f, 1.0f, 0.0f }};
const vector_n VECTOR_R_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f }};

const vector_n VECTOR_R_POS_4X_UNIT = { 4, { 1.0f, 0.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_POS_4Y_UNIT = { 4, { 0.0f, 1.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f, 0.0f }};
const vector_n VECTOR_R_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f }};

// Negative
const vector_n VECTOR_R_NEG_2X_UNIT = { 2, { -1.0f, 0.0 }};
const vector_n VECTOR_R_NEG_2Y_UNIT = { 2, { 0, -1.0f }};

const vector_n VECTOR_R_NEG_3X_UNIT = { 3, { -1.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f, 0.0f }};
const vector_n VECTOR_R_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f }};

const vector_n VECTOR_R_NEG_4X_UNIT = { 4, { -1.0f, 0.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f, 0.0f, 0.0f }};
const vector_n VECTOR_R_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f, 0.0f }};
const vector_n VECTOR_R_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f }};

/* Complex unit vectors */

const vector_n VECTOR_C_POS_2X_UNIT = { 2, { 1.0f * I, 0.0 }};
const vector_n VECTOR_C_POS_2Y_UNIT = { 2, { 0, 1.0f * I }};

const vector_n VECTOR_C_POS_3X_UNIT = { 3, { 1.0f * I, 0.0f, 0.0f }};
const vector_n VECTOR_C_POS_3Y_UNIT = { 3, { 0.0f, 1.0f * I, 0.0f }};
const vector_n VECTOR_C_POS_3Z_UNIT = { 3, { 0.0f, 0.0f, 1.0f * I }};

const vector_n VECTOR_C_POS_4X_UNIT = { 4, { 1.0f * I, 0.0f, 0.0f, 0.0f }};
const vector_n VECTOR_C_POS_4Y_UNIT = { 4, { 0.0f, 1.0f * I, 0.0f, 0.0f }};
const vector_n VECTOR_C_POS_4Z_UNIT = { 4, { 0.0f, 0.0f, 1.0f * I, 0.0f }};
const vector_n VECTOR_C_POS_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, 1.0f * I }};

// Negative
const vector_n VECTOR_C_NEG_2X_UNIT = { 2, { -1.0f * I, 0.0 }};
const vector_n VECTOR_C_NEG_2Y_UNIT = { 2, { 0, -1.0f * I }};

const vector_n VECTOR_C_NEG_3X_UNIT = { 3, { -1.0f * I, 0.0f, 0.0f }};
const vector_n VECTOR_C_NEG_3Y_UNIT = { 3, { 0.0f, -1.0f * I, 0.0f }};
const vector_n VECTOR_C_NEG_3Z_UNIT = { 3, { 0.0f, 0.0f, -1.0f * I }};

const vector_n VECTOR_C_NEG_4X_UNIT = { 4, { -1.0f * I, 0.0f, 0.0f, 0.0f }};
const vector_n VECTOR_C_NEG_4Y_UNIT = { 4, { 0.0f, -1.0f * I, 0.0f, 0.0f }};
const vector_n VECTOR_C_NEG_4Z_UNIT = { 4, { 0.0f, 0.0f, -1.0f * I, 0.0f }};
const vector_n VECTOR_C_NEG_4W_UNIT = { 4, { 0.0f, 0.0f, 0.0f, -1.0f * I }};

/* vector functions */

// Equality

bool m_vector_equal(vector_n u, vector_n v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {return false;}

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        if (u.elements[i] == v.elements[i]) {
            return true;
        }
    }
    return false;
}

// Add

vector_n m_vector_add(vector_n u, vector_n v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_FATAL("Action undefined on vectors off different sizes: %f and %f", sizeof(u)/sizeof(u.elements[0]), sizeof(v)/sizeof(v.elements[0]));
        exit(1);
    }

    vector_n sum = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        sum.elements[i] = u.elements[i] + v.elements[i];
    }
    return sum;
}

// Subtract

vector_n m_vector_sub(vector_n u, vector_n v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_FATAL("Action undefined on vectors off different sizes: %f and %f", sizeof(u)/sizeof(u.elements[0]), sizeof(v)/sizeof(v.elements[0]));
        exit(1);
    }

    vector_n diff = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        diff.elements[i] = u.elements[i] - v.elements[i];
    }
    return diff;
}

// Multi

vector_n m_vector_multi(vector_n u, vector_n v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_FATAL("Action undefined on vectors off different sizes: %f and %f", sizeof(u)/sizeof(u.elements[0]), sizeof(v)/sizeof(v.elements[0]));
        exit(1);
    }

    vector_n product = { .n = ARRAY_SIZE(v) };

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        product.elements[i] = u.elements[i] * v.elements[i];
    }
    return product;
}

// Dot Product

u32 m_vector_dot(vector_n u, vector_n v) {

    if (ARRAY_SIZE(u) != ARRAY_SIZE(u)) {
	      LOG_FATAL("Action undefined on vectors off different sizes: %f and %f", sizeof(u)/sizeof(u.elements[0]), sizeof(v)/sizeof(v.elements[0]));
        exit(1);
    }

    u32 product;

    for (u32 i = 0; i < ARRAY_SIZE(v); i++) {
        product += u.elements[i] * v.elements[i];
    }
    return product;
}

// Cross Product

vector_n m_vector_x(vector_n, vector_n);
