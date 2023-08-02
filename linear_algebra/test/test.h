#ifndef _H_TEST
#define _H_TEST

#include "../../const.h"
#include "../../defines.h"
#include "../vectors.h"
#include "../matrices.h"
#include "../../memory/memory.h"
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

bool test_m_vector_equal(m_vector, m_vector, m_vector);

// Add

bool test_m_vector_add(m_vector, m_vector, m_vector);

// Subtract

bool test_m_vector_sub(m_vector, m_vector, m_vector);

// Multi

bool test_m_vector_multi(m_vector, m_vector, m_vector);

// Dot Product

bool test_m_vector_dot(m_vector, m_vector, f32);

// Cross Product

bool test_m_vector_x(m_vector, m_vector, m_vector);

#endif
