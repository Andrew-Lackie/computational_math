#ifndef _H_TEST
#define _H_TEST

#include "../../const.h"
#include "../../defines.h"
#include "../vectors.h"
#include "../matrices.h"
#include "../../assert/logger.h"
#include "../../assert/asserts.h"

#if LOG_ASSERT
#undef LOG_DEBUG_ENABLED
#undef LOG_TRACE_ENABLED
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#endif

f32 double_el(f32 num);

/* vector creation */

bool test_vector(size_t dim, f32*, ...);

bool test_vector_n(size_t dim, f32*, f32*);

bool test_vector_f(size_t dim, f32*, f32 (*f)(f32), f32*);

/* vector operations */

// Equality

bool test_vec_equal(vec, vec, vec);

// Add

bool test_vec_add(vec, vec, vec);

// Subtract

bool test_vec_sub(vec, vec, vec);

// Multi

bool test_vec_multi(vec, vec, vec);

// Dot Product

bool test_vec_dot(vec, vec, f32);

// Cross Product

bool test_vec_x(vec, vec, vec);

#endif
