#ifndef VECTOR_R

#define VECTOR_R

/* Vector Class */

#include "vector.h"
#include "array.h"

typedef struct {
	void* sub;
	Array* super;
}o_Vector;

#endif