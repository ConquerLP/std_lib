#ifndef VECTOR_H

#define VECTOR_H

#include "object.h"
#include <stdlib.h>

enum {
	VEC_AXIS_X = 0,
	VEC_AXIS_Y,
	VEC_AXIS_Z,
	VEC_AXIS_LAST,
};  
extern size_t VEC_AXIS[VEC_AXIS_LAST];

typedef struct _VectorIF {
	long double (*get)(void* obj, size_t index);
	void (*set)(void* obj, size_t index, double value);
	double (*calcDotP)(void* vec1, void* vec2);
	void (*rotate3D)(void* obj, double angle, size_t axis); //3D only
	void (*rotate2D)(void* obj, double angle); //2D only
	double (*getLength)(void* obj);
	double (*getAngle)(void* vec1, void* vec2);
}VectorIF;

typedef struct _Vector {
	void* super;
	void* self;
	VectorIF* _VectorIF;
	ObjectIF* o_IF;
}Vector;

Vector* Vector_ctor(size_t data_type, size_t dim, ...);
Vector* Vector_sum(size_t data_type, void* vec1, void* vec2);

#endif // !VECTOR_H
