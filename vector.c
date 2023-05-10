#include "vector.h"
#include "vector.r"

#include "object.h"
#include "object.r"

#include "def.h"
#include "basic.h"

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "std_lib_math.h"

/* function prototpyes */
/* overriding Object methods */
private_fun char* Vector3D_toString(void* obj);
private_fun void* Vector3D_clone(void* obj);
private_fun void Vector3D_dtor(void* obj);
private_fun boolean Vector3D_equals(void* obj, void* obj2);

/* Vector3D methods */
private_fun double Vector3D_get(void* obj, char index);
private_fun void Vector3D_set(void* obj, char index, double value);
private_fun double Vector3D_calcDotP(void* vec1, void* vec2);
private_fun void Vector3D_rotate(void* obj, double angle, char axis);
private_fun double Vector3D_getLength(void* obj);

/* pulbic functions */
Vector3D* Vector3D_ctor(double x, double y, double z)
{
	Object* super = Object_ctor("Vector3D");
	Vector3D* this;
	Vector3DIF* thisIF;
	o_Vector3D* self;
	MALLOC(Vector3D, 1, this);
	MALLOC(Vector3DIF, 1, thisIF);
	MALLOC(o_Vector3D, 1, self);
	((o_Object*)super->self)->sub = this;
	this->super = super;
	this->self = self;
	this->vector3dIF = thisIF;
	this->objectIF = super->objectIF;

	super->objectIF->toString = &Vector3D_toString;
	super->objectIF->clone = &Vector3D_clone;
	super->objectIF->dtor = &Vector3D_dtor;
	super->objectIF->equals = &Vector3D_equals;

	thisIF->get = &Vector3D_get;
	thisIF->set = &Vector3D_set;
	thisIF->calcDotP = &Vector3D_calcDotP;
	thisIF->rotate = &Vector3D_rotate;
	thisIF->getLength = &Vector3D_getLength;

	self->sub = NULL;
	self->toString = basic_strcpy("");
	self->values[0] = x;
	self->values[1] = y;
	self->values[2] = z;
	return this;
}

/* overriding Object methods */
private_fun char* Vector3D_toString(void* obj)
{
	CAST(Vector3D, obj, NULL, );
	FREE(self->toString);
	char* tmp;
	MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	snprintf(tmp, 100, "X: %lf\nY: %lf\nZ: %lf\n", self->values[0], self->values[1], self->values[2]);
	self->toString = basic_strcpy(tmp);
	FREE(tmp);
	return self->toString;
}

private_fun void* Vector3D_clone(void* obj)
{
	CAST(Vector3D, obj, NULL, );
	return Vector3D_ctor(self->values[0], self->values[1], self->values[2]);
}

private_fun void Vector3D_dtor(void* obj)
{
	CAST(Vector3D, obj, , );
	FREE(self->toString);
	FREE(this->vector3dIF);
	Object_dtor(this->super);
	FREE(this);
}

private_fun boolean Vector3D_equals(void* obj, void* obj2)
{
	CAST(Vector3D, obj, false, );
	CAST(Vector3D, obj2, false, 1);
	for (size_t i = 0; i < 3; ++i) {
		if (self->values[i] != self1->values[i]) return false;
	}
	return true;
}

/* Vector3D methods */
private_fun double Vector3D_get(void* obj, char index)
{
	CAST(Vector3D, obj, 0.0, );
	switch (index) {
	case 'x': return self->values[0]; break;
	case 'y': return self->values[1]; break;
	case 'z': return self->values[2]; break;
	default: return 0.0; break;
	}
}

private_fun void Vector3D_set(void* obj, char index, double value)
{
	CAST(Vector3D, obj, , );
	switch (index) {
	case 'x': self->values[0] = value; break;
	case 'y': self->values[1] = value; break;
	case 'z': self->values[2] = value; break;
	default: ; break;
	}
}

private_fun double Vector3D_calcDotP(void* vec1, void* vec2)
{
	CAST(Vector3D, vec1, 0.0, );
	CAST(Vector3D, vec2, 0.0, 1);
	return self->values[0] * self1->values[0] + self->values[1] * self1->values[1] + self->values[2] * self1->values[2];
}

private_fun double Vector3D_angle(void* vec1, void* vec2)
{
	return acos(Vector3D_calcDotP(vec1, vec2) / (Vector3D_getLength(vec1) * Vector3D_getLength(vec2)));
}

private_fun void Vector3D_rotate(void* obj, double angle, char axis)
{
	CAST(Vector3D, obj, , );
	double tmp0 = 0.0;
	double tmp1 = 0.0;
	switch (axis) {
	case 'x': {
		tmp0 = self->values[1] * cos(std_lib_math_degToRad(angle)) + (-1) * cos(std_lib_math_degToRad(angle)) * self->values[2];
		tmp1 = self->values[1] * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * self->values[2];
		self->values[1] = tmp0;
		self->values[2] = tmp1;
	} break;
	case 'y': {
		tmp0 = self->values[0] * cos(std_lib_math_degToRad(angle)) + sin(std_lib_math_degToRad(angle)) * self->values[2];
		tmp1 = self->values[0] * (-1) * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * self->values[2];
		self->values[0] = tmp0;
		self->values[2] = tmp1;
	} break;
	case 'z': {
		tmp0 = self->values[0] * cos(std_lib_math_degToRad(angle)) + (-1) * sin(std_lib_math_degToRad(angle)) * self->values[1];
		tmp1 = self->values[0] * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * self->values[1];
		self->values[0] = tmp0;
		self->values[1] = tmp1;
	} break;
	default:; break;
	}
}

private_fun double Vector3D_getLength(void* obj)
{
	CAST(Vector3D, obj, 0.0, );
	return sqrt(
		self->values[0] * self->values[0] +
		self->values[1] * self->values[1] +
		self->values[2] * self->values[2]
	);
}