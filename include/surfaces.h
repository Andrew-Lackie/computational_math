#ifndef _SURFACES_H
#define _SURFACES_H

#include "vectors.h"

struct triangle {
	vec p[3];
};

struct mesh {
	triangle *tris;
};

#endif
