#ifndef VECTOR_H

#define VECTOR_H

#include "object.h"
#include <stdlib.h>

typedef enum {
	VT_INT = 0,
	VT_FLOAT,
	VT_DOUBLE,
	VT_SIZE_T,
	VT_COUNT
}Vector_types;


typedef enum {
	VA_X = 0,
	VA_Y,
	VA_Z,
	VA_COUNT
}Vector_axis;

typedef struct _VectorIF {
	double (*get)(void* obj, unsigned int index);
	void (*set)(void* obj, unsigned int index, double value);
	double (*calcDotP)(void* vec1, void* vec2);
	void (*rotate3D)(void* obj, double angle, Vector_axis axis); //3D only
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

Vector* Vector_ctor(Vector_types t, size_t dim, ...);
Vector* Vector_sum(Vector_types t, void* vec1, void* vec2);

#endif // !VECTOR_H
