#ifndef VECTOR_R

#define VECTOR_R

/* Vector Class */

#include "vector.h"
#include "array.h"

typedef struct {
	void* sub;
	Array* values;
	Vector_types type;
	size_t dim;
}o_Vector;

#endif