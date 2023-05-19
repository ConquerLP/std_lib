#ifndef VECTOR_H

#define VECTOR_H

#include "object.h"
#include <stdlib.h>

typedef struct _Vector3DIF {
	double (*get)(void* obj, char index);
	void (*set)(void* obj, char index, double value);
	double (*calcDotP)(void* vec1, void* vec2);
	void (*rotate)(void* obj, double angle, char axis);
	double (*getLength)(void* obj);
	double (*getAngle)(void* vec1, void* vec2);
}Vector3DIF;

typedef struct _Vector3D {
	void* super;
	void* self;
	Vector3DIF* vector3dIF;
	ObjectIF* objectIF;
}Vector3D;

Vector3D* Vector3D_ctor(double x, double y, double z);

#endif // !VECTOR_H
