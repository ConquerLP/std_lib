#include "vector.h"
#include "vector.r"

#include "object.h"
#include "object.r"

#include "string.h"
#include "string.r"

#include "def.h"
#include "basic.h"

#include <stdarg.h>
#include <stdlib.h>
#include "std_lib_math.h"

/* MACROS */
#define VECTOR_INIT(datatype, def_datatype) \
	tmp = Array_ctor(def_datatype, dim); \
	va_list arg; \
	va_start(arg, dim); \
	datatype value; \
	for (size_t i = 0; i < dim; ++i) { \
		value = va_arg(arg, datatype); \
		tmp->_ArrayIF->set(tmp, &value, i); \
	} \
	va_end(arg); 

size_t VEC_AXIS[VEC_AXIS_LAST] = {
	VEC_AXIS_X,
	VEC_AXIS_Y,
	VEC_AXIS_Z
};

/* function prototpyes */
/* overriding Object methods */
private_fun char* Vector_toString(void* obj);
private_fun void* Vector_clone(void* obj);
private_fun void Vector_dtor(void* obj);
private_fun boolean Vector_equals(void* obj, void* obj2);

/* Vector methods */
private_fun long double Vector_get(void* obj, size_t index);
private_fun void Vector_set(void* obj, size_t index, double value);
private_fun double Vector_calcDotP(void* vec1, void* vec2);
private_fun void Vector_rotate3D(void* obj, double angle, size_t axis);
private_fun void Vector_rotate2D(void* obj, double angle);
private_fun double Vector_getLength(void* obj);
private_fun double Vector_angle(void* vec1, void* vec2);

/* helper fucntions */
private_fun void Vector_setDim(void* obj, size_t dim);
boolean Vector_isAllowedType(size_t datatype);

/* pulbic functions */
Vector* Vector_ctor(size_t datatype, size_t dim, ...)
{
	if (!Vector_isAllowedType(datatype)) return NULL;
	if (dim <= 0) return NULL;
	BASIC_CTOR(Vector);
	super->o_IF->toString = &Vector_toString;
	super->o_IF->clone = &Vector_clone;
	super->o_IF->dtor = &Vector_dtor;
	super->o_IF->equals = &Vector_equals;
	thisIF->get = &Vector_get;
	thisIF->set = &Vector_set;
	thisIF->calcDotP = &Vector_calcDotP;
	thisIF->rotate3D = &Vector_rotate3D;
	thisIF->rotate2D = &Vector_rotate2D;
	thisIF->getLength = &Vector_getLength;
	thisIF->getAngle = &Vector_angle;
	self->sub = NULL;
	Array* tmp = NULL;
	switch (datatype) {
		case DEF_USHORT:		{ VECTOR_INIT(unsigned short, DEF_USHORT); break; }
		case DEF_SHORT:			{ VECTOR_INIT(short, DEF_SHORT); break; }
		case DEF_UINT:			{ VECTOR_INIT(unsigned int, DEF_UINT); break; }
		case DEF_INT:			{ VECTOR_INIT(int, DEF_INT); break; }
		case DEF_ULONGINT:		{ VECTOR_INIT(unsigned long int, DEF_ULONGINT); break; }
		case DEF_LONGINT:		{ VECTOR_INIT(long int, DEF_LONGINT); break; }
		case DEF_LONGLONGINT:	{ VECTOR_INIT(long long int, DEF_LONGLONGINT); break; }
		case DEF_SIZE_T:		{ VECTOR_INIT(size_t, DEF_SIZE_T); break; }
		case DEF_FLOAT:			{ VECTOR_INIT(float, DEF_FLOAT); break; }
		case DEF_DOUBLE:		{ VECTOR_INIT(double, DEF_DOUBLE); break; }
		case DEF_LONGDOUBLE:	{ VECTOR_INIT(long double, DEF_LONGDOUBLE); break; }
		default:				return NULL;
	}
	self->values = tmp;
	self->type = datatype;
	return this;
}


/* overriding Object methods */
private_fun char* Vector_toString(void* obj)
{
	CAST(Vector, obj, NULL, );
	CAST_OBJECT(this->super, NULL, 1);
	_FREE(self1->toString);
	String* str = String_ctor("");
	CAST(String, str, NULL, 2);
	char* tmp;
	_MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	for (size_t i = 0; i < self->dim; ++i) {
		snprintf(tmp, 100, "V(%zu): %lf\n", i, Vector_get(obj, i));
		str->_StringIF->append(str, tmp);
	}
	self1->toString = basic_strcpy(self2->str);
	delete(str);
	_FREE(tmp);
	return self1->toString;
}

private_fun void* Vector_clone(void* obj)
{
	CAST(Vector, obj, NULL, );
	Vector* tmp = Vector_ctor(self->type, 1, 0.0);
	Vector_setDim(tmp, self->dim);
	for (size_t i = 0; i < self->dim; ++i) {
		Vector_set(tmp, i, Vector_get(obj, i));
	}
	return tmp;
}

private_fun void Vector_dtor(void* obj)
{
	CAST(Vector, obj, , );
	_FREE(this->_VectorIF);
	_FREE(self->values);
	delete(self->values);
	Object_dtor(this->super);
	FREE(this);
}

private_fun boolean Vector_equals(void* obj, void* obj2)
{
	CAST(Vector, obj, false, );
	CAST(Vector, obj2, false, 1);
	if (self->dim != self1->dim) return false;
	for (size_t i = 0; i < self->dim; ++i) {
		if (Vector_get(obj, i) != Vector_get(obj2, i)) return false;
	}
	return true;
}

/* Vector methods */
private_fun long double Vector_get(void* obj, size_t index)
{
	CAST(Vector, obj, 0.0, );
	long double* result = self->values->_ArrayIF->get(self->values, index);
	return *result;
}

private_fun void Vector_set(void* obj, size_t index, double value)
{
	CAST(Vector, obj, , );
	self->values->_ArrayIF->set(self->values, &value, index);
}

private_fun double Vector_calcDotP(void* vec1, void* vec2)
{
	CAST(Vector, vec1, 0.0, );
	CAST(Vector, vec2, 0.0, 1);
	if (self->dim != self1->dim) return 0.0;
	double result = 0.0;
	for (size_t i = 0; i < self->dim; ++i) {
		result += Vector_get(vec1, i) * Vector_get(vec2, i);
	}
	return result;
}

private_fun double Vector_angle(void* vec1, void* vec2)
{
	return acos(Vector_calcDotP(vec1, vec2) / (Vector_getLength(vec1) * Vector_getLength(vec2)));
}

private_fun void Vector_rotate3D(void* obj, double angle, size_t axis)
{
	CAST(Vector, obj, , );
	if (self->dim != 3) return;
	double tmp0 = 0.0;
	double tmp1 = 0.0;
	switch (axis) {
	case VEC_AXIS_X: {
		tmp0 = Vector_get(obj, 1) * cos(std_lib_math_degToRad(angle)) + (-1) * cos(std_lib_math_degToRad(angle)) * Vector_get(obj, 2);
		tmp1 = Vector_get(obj, 1) * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * Vector_get(obj, 2);
		Vector_set(obj, 1, tmp0);
		Vector_set(obj, 2, tmp1);
	} break;
	case VEC_AXIS_Y: {
		tmp0 = Vector_get(obj, 0) * cos(std_lib_math_degToRad(angle)) + sin(std_lib_math_degToRad(angle)) * Vector_get(obj, 2);
		tmp1 = Vector_get(obj, 0) * (-1) * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * Vector_get(obj, 2);
		Vector_set(obj, 0, tmp0);
		Vector_set(obj, 2, tmp1);
	} break;
	case VEC_AXIS_Z: {
		tmp0 = Vector_get(obj, 0) * cos(std_lib_math_degToRad(angle)) + (-1) * sin(std_lib_math_degToRad(angle)) * Vector_get(obj, 1);
		tmp1 = Vector_get(obj, 0) * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * Vector_get(obj, 1);
		Vector_set(obj, 0, tmp0);
		Vector_set(obj, 1, tmp1);
	} break;
	default:; break;
	}
}

private_fun void Vector_rotate2D(void* obj, double angle)
{
	CAST(Vector, obj, , );
	if (self->dim != 2) return;
	double tmp0 = 0.0;
	double tmp1 = 0.0;
	tmp0 = Vector_get(obj, 0) * cos(std_lib_math_degToRad(angle)) + (-1) * sin(std_lib_math_degToRad(angle)) * Vector_get(obj, 1);
	tmp1 = Vector_get(obj, 0) * sin(std_lib_math_degToRad(angle)) + cos(std_lib_math_degToRad(angle)) * Vector_get(obj, 1);
	Vector_set(obj, 0, tmp0);
	Vector_set(obj, 1, tmp1);
}

private_fun double Vector_getLength(void* obj)
{
	CAST(Vector, obj, 0.0, );
	double sum = 0.0;
	for (size_t i = 0; i < self->dim; ++i) {
		sum += Vector_get(obj, i) * Vector_get(obj, i);
	}
	return sqrt(sum);
}

/* helper functions */
private_fun void Vector_setDim(void* obj, size_t dim)
{
	CAST(Vector, obj, , );
	if (dim <= 0) return;
	if (dim == self->dim) return;
	self->values->_ArrayIF->resize(self->values, dim);
	self->dim = dim;
}

boolean Vector_isAllowedType(size_t datatype)
{
	if (datatype < DEF_USHORT) return false;
	if (datatype > DEF_LONGDOUBLE) return false;
	else return true;
}