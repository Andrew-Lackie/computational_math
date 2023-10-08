#ifndef _LU_H
#define _LU_H

#include <math.h>
#include "vectors.h"
#include "matrices.h"
#include "const.h"

void lu_dcmp(mat*, vec*, f32*);

void lubskb(mat*, vec*, vec);

#endif
