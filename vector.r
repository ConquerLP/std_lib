#ifndef VECTOR_R

#define VECTOR_R

/* Vector Class */

#include "Vector.h"

typedef struct {
	void* sub;
	void* values;
	Vector_types type;
	unsigned int dim;
}o_Vector;

#endif