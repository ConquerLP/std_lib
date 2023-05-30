#ifndef VECTOR_H

#define VECTOR_H

#include "object.h"
#include <stdlib.h>

typedef enum {
	VT_INT = 0,
	VT_FLOAT,
	VT_DOUBLE,
	VT_UNSIGNED_INT,
	VT_COUNT
}Vector_types;

typedef struct _VectorIF {
	double (*get)(void* obj, unsigned int index);
	void (*set)(void* obj, unsigned int index, double value);
	double (*calcDotP)(void* vec1, void* vec2);
	void (*rotate)(void* obj, double angle, unsigned int axis); //for 2D and 3D only
	double (*getLength)(void* obj);
	double (*getAngle)(void* vec1, void* vec2);
}VectorIF;

typedef struct _Vector {
	void* super;
	void* self;
	VectorIF* _VectorIF;
	ObjectIF* o_IF;
}Vector;

Vector* Vector_ctor(Vector_types t, unsigned int dim, ...);
Vector* Vector_sum(Vector_types t, void* vec1, void* vec2);

#endif // !VECTOR_H
