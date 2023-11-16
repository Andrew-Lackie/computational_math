#ifndef _GAUSSJ_H
#define _GAUSSJ_H

#include "ivectors.h"
#include "fvectors.h"
#include "matrices.h"

#define SWAP(a,b) {temp = (a);(a) = (b);(b) = temp;}

void gaussj_dcmp(matrix *a, matrix *b);

#endif
