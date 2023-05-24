#ifndef VECTOR_H

#define VECTOR_H

#include "object.h"
#include <stdlib.h>

typedef struct _VectorIF {
	double (*get)(void* obj, char index);
	void (*set)(void* obj, char index, double value);
	double (*calcDotP)(void* vec1, void* vec2);
	void (*rotate)(void* obj, double angle, char axis);
	double (*getLength)(void* obj);
	double (*getAngle)(void* vec1, void* vec2);
}VectorIF;

typedef struct _Vector {
	void* super;
	void* self;
	VectorIF* _VectorIF;
	ObjectIF* o_IF;
}Vector;

Vector* Vector_ctor(double x, double y, double z);

#endif // !VECTOR_H
