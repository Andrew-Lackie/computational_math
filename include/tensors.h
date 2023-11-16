#ifndef _TENSORS_H
#define _TENSORS_H

#include <vectors.h>

// Generic tensor...could be a tensor of vectors, or matrices, or tensors, or tensors of tensors, or tensors of tensors of tensors of vectors of floats, or a tensor of tensors of tensors of vectors of matrices of floats, or a rank 0 tensor of 1 undirected int.

typedef struct { size_t rank; vector elements; } tensor;

#define TENSOR_INIT(tensor, rank, capacity) {\
    VECTOR_INIT(elements, capacity) \
    tensor->elements = elements;\
    tensor->rank = rank;\
    }
#define TENSOR_SET(tensor, type, id, item) VECTOR_SET(tensor.elements, type, id, item)
#define TENSOR_GET(tensor, type, id) VECTOR_GET(tensor.elements, type, id)
#define TENSOR_ADD(tensor, type, item) VECTOR_ADD(tensor.elements, type, item)
#define TENSOR_DELETE(tensor, id) VECTOR_DELETE(tensor.elements, id)
#define TENSOR_N(tensor) VECTOR_TOTAL(tensor.elements)
#define TENSOR_M(tensor) tensor.m
#define TENSOR_FREE(tensor) VECTOR_FREE(tensor.elements)

#endif
