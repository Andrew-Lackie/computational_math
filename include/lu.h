#ifndef _LU_H
#define _LU_H

#include <math.h>
#include "fvectors.h"
#include "matrices.h"
#include "const.h"

void lu_dcmp(matrix*, vector*, f32*);

void lubskb(matrix*, vector*, vector);

#endif
