#include "vector.h"
#include "vector.r"

#include "object.h"
#include "object.r"

#include "def.h"
#include "basic.h"

#include <stdarg.h>
#include <stdlib.h>
#include "std_lib_math.h"

/* MACROS */
#define VECTOR_SET(datatype) \
	datatype* values; \
	_MALLOC(datatype, dim, values); \
	va_list arg; \
	va_start(arg, dim); \
	for (size_t i = 0; i < dim; ++i) { \
		values[i] = va_arg(arg, datatype); \
	} \
	va_end(arg); 

/* function prototpyes */
/* overriding Object methods */
private_fun char* Vector_toString(void* obj);
private_fun void* Vector_clone(void* obj);
private_fun void Vector_dtor(void* obj);
private_fun boolean Vector_equals(void* obj, void* obj2);

/* Vector methods */
private_fun double Vector_get(void* obj, char index);
private_fun void Vector_set(void* obj, char index, double value);
private_fun double Vector_calcDotP(void* vec1, void* vec2);
private_fun void Vector_rotate(void* obj, double angle, char axis);
private_fun double Vector_getLength(void* obj);
private_fun double Vector_angle(void* vec1, void* vec2);

/* pulbic functions */
Vector* Vector_ctor(Vector_types t, unsigned int dim, ...)
{
	if (t >= VT_COUNT) return NULL;
	if (dim <= 0) return NULL;
	BASIC_CTOR(Vector);
	super->o_IF->toString = &Vector_toString;
	super->o_IF->clone = &Vector_clone;
	super->o_IF->dtor = &Vector_dtor;
	super->o_IF->equals = &Vector_equals;

	thisIF->get = &Vector_get;
	thisIF->set = &Vector_set;
	thisIF->calcDotP = &Vector_calcDotP;
	thisIF->rotate = &Vector_rotate;
	thisIF->getLength = &Vector_getLength;
	thisIF->getAngle = &Vector_angle;

	self->sub = NULL;
	switch (t) {
	case VT_INT: {
		VECTOR_SET(int);
		break;
	}
	case VT_FLOAT: {
		VECTOR_SET(float);
		break;
	}
	case VT_DOUBLE: {
		VECTOR_SET(double);
		break;
	}
	case VT_UNSIGNED_INT: {
		VECTOR_SET(unsigned int);
		break;
	}
	default: return NULL;
	}
	return this;
}


/* overriding Object methods */
private_fun char* Vector_toString(void* obj)
{
	CAST(Vector, obj, NULL, );
	CAST_OBJECT(this->super, NULL, 1);
	_FREE(self1->toString);
	char* tmp;
	MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	snprintf(tmp, 100, "X: %lf\nY: %lf\nZ: %lf\n", self->values[0], self->values[1], self->values[2]);
	self1->toString = basic_strcpy(tmp);
	_FREE(tmp);
	return self1->toString;
}

private_fun void* Vector_clone(void* obj)
{
	CAST(Vector, obj, NULL, );
	return Vector_ctor(self->values[0], self->values[1], self->values[2]);
}

private_fun void Vector_dtor(void* obj)
{
	CAST(Vector, obj, , );
	_FREE(this->_VectorIF);
	Object_dtor(this->super);
	FREE(this);
}

private_fun boolean Vector_equals(void* obj, void* obj2)
{
	CAST(Vector, obj, false, );
	CAST(Vector, obj2, false, 1);
	for (size_t i = 0; i < 3; ++i) {
		if (self->values[i] != self1->values[i]) return false;
	}
	return true;
}

/* Vector methods */
private_fun double Vector_get(void* obj, char index)
{
	CAST(Vector, obj, 0.0, );
	switch (index) {
	case 'x': return self->values[0]; break;
	case 'y': return self->values[1]; break;
	case 'z': return self->values[2]; break;
	default: return 0.0; break;
	}
}

private_fun void Vector_set(void* obj, char index, double value)
{
	CAST(Vector, obj, , );
	switch (index) {
	case 'x': self->values[0] = value; break;
	case 'y': self->values[1] = value; break;
	case 'z': self->values[2] = value; break;
	default:; break;
	}
}

private_fun double Vector_calcDotP(void* vec1, void* vec2)
{
	CAST(Vector, vec1, 0.0, );
	CAST(Vector, vec2, 0.0, 1);
	return self->values[0] * self1->values[0] + self->values[1] * self1->values[1] + self->values[2] * self1->values[2];
}

private_fun double Vector_angle(void* vec1, void* vec2)
{
	return acos(Vector_calcDotP(vec1, vec2) / (Vector_getLength(vec1) * Vector_getLength(vec2)));
}

private_fun void Vector_rotate(void* obj, double angle, char axis)
{
	CAST(Vector, obj, , );
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

private_fun double Vector_getLength(void* obj)
{
	CAST(Vector, obj, 0.0, );
	return sqrt(
		self->values[0] * self->values[0] +
		self->values[1] * self->values[1] +
		self->values[2] * self->values[2]
	);
}
