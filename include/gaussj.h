#ifndef _GAUSSJ_H
#define _GAUSSJ_H

#include "vectors.h"
#include "matrices.h"

#define SWAP(a,b) {temp = (a);(a) = (b);(b) = temp;}

void gaussj(mat *a, mat *b);

#endif
