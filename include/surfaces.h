#ifndef _SURFACES_H
#define _SURFACES_H

#include "vectors.h"

struct triangle {
	vector p[3];
};

struct mesh {
	vector *tris;
};

#endif
