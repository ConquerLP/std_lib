#include "vector.h"
#include "vector.r"

#include "object.h"
#include "object.r"

#include "string.h"
#include "string.r"

#include "array.h"
#include "array.r"

#include "def.h"
#include "basic.h"

#include <stdarg.h>
#include <stdlib.h>
#include "std_lib_math.h"

/* MACROS */
#define VECTOR_INIT(data_type, def_data_type) \
	tmp = Array_ctor(def_data_type, dim); \
	va_list arg; \
	va_start(arg, dim); \
	data_type value; \
	for (size_t i = 0; i < dim; ++i) { \
		value = va_arg(arg, data_type); \
		tmp->_ArrayIF->set(tmp, &value, i); \
	} \
	va_end(arg); 

#define VECTOR_ROTATE_3D(data_type) \
	data_type x, y, z; \
	x = _getV(data_type, obj, 0); \
	y = _getV(data_type, obj, 2); \
	z = _getV(data_type, obj, 3); \
	data_type tmp0; \
	data_type tmp1; \
	switch (axis) { \
		case VEC_AXIS_X: { \
			tmp0 = y * (data_type)cos(std_lib_math_degToRad(angle)) + (-1) * (data_type)cos(std_lib_math_degToRad(angle)) * z; \
			tmp1 = y * (data_type)sin(std_lib_math_degToRad(angle)) + (data_type)cos(std_lib_math_degToRad(angle)) * z; \
			self->super->_ArrayIF->set(self->super, &tmp0, 1); \
			self->super->_ArrayIF->set(self->super, &tmp1, 2); \
		} break; \
		case VEC_AXIS_Y: { \
			tmp0 = x * (data_type)cos(std_lib_math_degToRad(angle)) + (data_type)sin(std_lib_math_degToRad(angle)) * z; \
			tmp1 = x * (-1) * (data_type)sin(std_lib_math_degToRad(angle)) + (data_type)cos(std_lib_math_degToRad(angle)) * z; \
			self->super->_ArrayIF->set(self->super, &tmp0, 0); \
			self->super->_ArrayIF->set(self->super, &tmp1, 2); \
		} break; \
		case VEC_AXIS_Z: { \
			tmp0 = x * (data_type)cos(std_lib_math_degToRad(angle)) + (-1) * (data_type)sin(std_lib_math_degToRad(angle)) * y; \
			tmp1 = x * (data_type)sin(std_lib_math_degToRad(angle)) + (data_type)cos(std_lib_math_degToRad(angle)) * y; \
			self->super->_ArrayIF->set(self->super, &tmp0, 0); \
			self->super->_ArrayIF->set(self->super, &tmp1, 1); \
		} break; \
		default:; break; \
	} 

#define VECTOR_ROTATE_2D(data_type) \
	data_type x, y; \
	data_type tmp0, tmp1; \
	x = _getV(data_type, obj, 0); \
	y = _getV(data_type, obj, 1); \
	tmp0 = x * (data_type)cos(std_lib_math_degToRad(angle)) + (-1) * (data_type)sin(std_lib_math_degToRad(angle)) * y; \
	tmp1 = x * (data_type)sin(std_lib_math_degToRad(angle)) + (data_type)cos(std_lib_math_degToRad(angle)) * y; \
	self->super->_ArrayIF->set(self->super, &tmp0, 0); \
	self->super->_ArrayIF->set(self->super, &tmp1, 1); 

#define VECTOR_SUM(data_type) \
	data_type value; \
	for (size_t i = 0; i < self2->length; ++i) { \
		value = _getV(data_type, vec1, i) + _getV(data_type, vec2, i); \
		self->super->_ArrayIF->set(self->super, &value, i); \
	} 

#define VECTOR_LENGTH(data_type) \
	data_type sum = 0; \
	for (size_t i = 0; i < self1->length; ++i) { \
		sum += _getV(data_type, obj, i) * _getV(data_type, obj, i); \
	} \
	return (double)sqrt((double)sum);

size_t VEC_AXIS[VEC_AXIS_LAST] = {
	VEC_AXIS_X,
	VEC_AXIS_Y,
	VEC_AXIS_Z
};

/* function prototpyes */
/* overriding Object methods */
private_fun void* Vector_clone(void* obj);
private_fun void Vector_dtor(void* obj);

/* Vector methods */
private_fun double Vector_calcDotP(void* vec1, void* vec2);
private_fun void Vector_rotate3D(void* obj, double angle, size_t axis);
private_fun void Vector_rotate2D(void* obj, double angle);
private_fun double Vector_getLength(void* obj);
private_fun double Vector_angle(void* vec1, void* vec2);

/* helper fucntions */
private_fun void Vector_setDim(void* obj, size_t dim);
boolean Vector_isAllowedType(size_t data_type);

/* pulbic functions */
Vector* Vector_ctor(size_t data_type, size_t dim, ...)
{
	if (!Vector_isAllowedType(data_type) || dim <= 0)  def_critical_error("Could not create new Vector");
	BASIC_CTOR(Vector);
	
	super->o_IF->clone = &Vector_clone;
	super->o_IF->dtor = &Vector_dtor;
	thisIF->calcDotP = &Vector_calcDotP;
	thisIF->rotate3D = &Vector_rotate3D;
	thisIF->rotate2D = &Vector_rotate2D;
	thisIF->getLength = &Vector_getLength;
	thisIF->getAngle = &Vector_angle;
	self->sub = NULL;
	Array* tmp = NULL;
	switch (data_type) {
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
	self->super = tmp;
	CAST(Array, tmp, NULL, 1);
	self1->sub = this;
	this->_ArrayIF = this1->_ArrayIF;
	super->o_IF->toString = this1->o_IF->toString;
	super->o_IF->equals = this->o_IF->equals;
	return this;
}

/* overriding Object methods */
private_fun void* Vector_clone(void* obj)
{
	CAST(Vector, obj, NULL, );
	CAST(Array, self->super, NULL, 1);
	Vector* tmp = Vector_ctor(self1->type, 1, 0.0);
	Vector_setDim(tmp, self1->length);
	for (size_t i = 0; i < self1->length; ++i) {
		this1->_ArrayIF->set(this1, this1->_ArrayIF->get(this1, i), i);
	}
	return tmp;
}

private_fun void Vector_dtor(void* obj)
{
	CAST(Vector, obj, , );
	_FREE(this->_VectorIF);
	delete(self->super);
	Object_dtor(this->super);
	FREE(this);
}

/* Vector methods */

private_fun double Vector_calcDotP(void* vec1, void* vec2)
{
	CAST(Vector, vec1, 0.0, );
	CAST(Vector, vec2, 0.0, 1);
	CAST(Array, self->super, 0.0, 2);
	CAST(Array, self1->super, 0.0, 3);
	if (self2->length != self3->length) return 0.0;
	double result = 0.0;
	for (size_t i = 0; i < self2->length; ++i) {
		switch (self2->type) {
			case DEF_USHORT:		result += _getV(unsigned short, vec1, i) * _getV(unsigned short, vec2, i); break;
			case DEF_SHORT:			result += _getV(short, vec1, i) * _getV(short, vec2, i); break;
			case DEF_UINT:			result += _getV(unsigned int, vec1, i) * _getV(unsigned int, vec2, i); break;
			case DEF_INT:			result += _getV(int, vec1, i) * _getV(int, vec2, i); break;
			case DEF_ULONGINT:		result += _getV(unsigned long int, vec1, i) * _getV(unsigned long int, vec2, i); break;
			case DEF_LONGINT:		result += _getV(long int, vec1, i) * _getV(long int, vec2, i); break;
			case DEF_LONGLONGINT:	result += _getV(long long int, vec1, i) * _getV(long long int, vec2, i); break;
			case DEF_SIZE_T:		result += _getV(size_t, vec1, i) * _getV(size_t, vec2, i); break;
			case DEF_FLOAT:			result += _getV(float, vec1, i) * _getV(float, vec2, i); break;
			case DEF_DOUBLE:		result += _getV(double, vec1, i) * _getV(double, vec2, i); break;
			case DEF_LONGDOUBLE:	result += _getV(long double, vec1, i) * _getV(long double, vec2, i); break;
			default:				def_critical_error("Could not calculate the dot product of two vectors");
		}
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
	CAST(Array, self->super, , 1);
	if (self1->length != 3) return;
	switch (self1->type) {
		case DEF_USHORT:			{VECTOR_ROTATE_3D(unsigned short); break;}
		case DEF_SHORT:				{VECTOR_ROTATE_3D(short); break;}
		case DEF_UINT:				{VECTOR_ROTATE_3D(unsigned int); break;}
		case DEF_INT:				{VECTOR_ROTATE_3D(int); break;}
		case DEF_ULONGINT:			{VECTOR_ROTATE_3D(unsigned long int); break;}
		case DEF_LONGINT:			{VECTOR_ROTATE_3D(long int); break;}
		case DEF_LONGLONGINT:		{VECTOR_ROTATE_3D(long long int); break;}
		case DEF_SIZE_T:			{VECTOR_ROTATE_3D(size_t); break;}
		case DEF_FLOAT:				{VECTOR_ROTATE_3D(float); break;}
		case DEF_DOUBLE:			{VECTOR_ROTATE_3D(double); break;}
		case DEF_LONGDOUBLE:		{VECTOR_ROTATE_3D(long double); break; }
		default:					def_critical_error("Could not rotate a vector");
	}
}

private_fun void Vector_rotate2D(void* obj, double angle)
{
	CAST(Vector, obj, , );
	CAST(Array, self->super, , 1);
	if (self1->length != 2) return;

	long double x = 0.0, y = 0.0;
	switch (self1->type) {
		case DEF_USHORT:		{VECTOR_ROTATE_2D(unsigned short); break;}
		case DEF_SHORT:			{VECTOR_ROTATE_2D(short); break;}
		case DEF_UINT:			{VECTOR_ROTATE_2D(unsigned int); break;}
		case DEF_INT:			{VECTOR_ROTATE_2D(int); break;}
		case DEF_ULONGINT:		{VECTOR_ROTATE_2D(unsigned long int); break;}
		case DEF_LONGINT:		{VECTOR_ROTATE_2D(long int); break;}
		case DEF_LONGLONGINT:	{VECTOR_ROTATE_2D(long long int); break;}
		case DEF_SIZE_T:		{VECTOR_ROTATE_2D(size_t); break;}
		case DEF_FLOAT:			{VECTOR_ROTATE_2D(float); break;}
		case DEF_DOUBLE:		{VECTOR_ROTATE_2D(double); break;}
		case DEF_LONGDOUBLE:	{VECTOR_ROTATE_2D(long double); break; }	
		default:				def_critical_error("Could not rotate a vector");
	}
}

private_fun double Vector_getLength(void* obj)
{
	CAST(Vector, obj, 0.0, );
	CAST(Array, self->super, 0.0, 1);
	switch (self1->type) {
		case DEF_USHORT:		{ VECTOR_LENGTH(unsigned short); break; }
		case DEF_SHORT:			{ VECTOR_LENGTH(short); break; }
		case DEF_UINT:			{ VECTOR_LENGTH(unsigned int); break; }
		case DEF_INT:			{ VECTOR_LENGTH(int); break; }
		case DEF_ULONGINT:		{ VECTOR_LENGTH(unsigned long int); break; }
		case DEF_LONGINT:		{ VECTOR_LENGTH(long int); break; }
		case DEF_LONGLONGINT:	{ VECTOR_LENGTH(long long int); break; }
		case DEF_SIZE_T:		{ VECTOR_LENGTH(size_t); break; }
		case DEF_FLOAT:			{ VECTOR_LENGTH(float); break; }
		case DEF_DOUBLE:		{ VECTOR_LENGTH(double); break; }
		case DEF_LONGDOUBLE:	{ VECTOR_LENGTH(long double); break; }
		default:				def_critical_error("Could not calculate the length of a vector");
	}
	return 0.0;
}

/* public functions */
Vector* Vector_sum(size_t data_type, void* vec1, void* vec2)
{
	CAST(Vector, vec1, NULL, );
	CAST(Vector, vec2, NULL, 1);
	CAST(Array, self->super, NULL, 2);
	CAST(Array, self1->super, NULL, 3);
	if (self2->length != self3->length) return NULL;
	Vector* sum = Vector_ctor(data_type, 1, 0.0);
	Vector_setDim(sum, self2->length);
	switch (self2->type) {
		case DEF_USHORT:		{VECTOR_SUM(unsigned short);}
		case DEF_SHORT:			{VECTOR_SUM(short);}
		case DEF_UINT:			{VECTOR_SUM(unsigned int);}
		case DEF_INT:			{VECTOR_SUM(int);}
		case DEF_ULONGINT:		{VECTOR_SUM(unsigned long int);}
		case DEF_LONGINT:		{VECTOR_SUM(long int);}
		case DEF_LONGLONGINT:	{VECTOR_SUM(long long int);}
		case DEF_SIZE_T:		{VECTOR_SUM(size_t);}
		case DEF_FLOAT:			{VECTOR_SUM(float);}
		case DEF_DOUBLE:		{VECTOR_SUM(double);}
		case DEF_LONGDOUBLE:	{VECTOR_SUM(long double); }
		default:				def_critical_error("Could not calculate the sum of two vectors");
	}
	return sum;
}

/* helper functions */
private_fun void Vector_setDim(void* obj, size_t dim)
{
	CAST(Vector, obj, , );
	CAST(Array, self->super, , 1);
	if (dim <= 0) return;
	if (dim == self1->length) return;
	self->super->_ArrayIF->resize(self->super, dim);
}

boolean Vector_isAllowedType(size_t data_type)
{
	if (data_type < DEF_USHORT) return false;
	if (data_type > DEF_LONGDOUBLE) return false;
	else return true;
}