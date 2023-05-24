#include "def.h"
#include "basic.h"

#include "array.h"
#include "array.r"

#include "object.h"
#include "object.r"

#include "string.h"
#include "string.r"

#include <stdlib.h>
#include <stdio.h>

/* MACROS */

#define ARRAY_SET_PRIMITIVE(datatype) \
	if(basic_strcmp(self->name, #datatype)) { \
		datatype* tmp; \
		_MALLOC(datatype, 1, tmp); \
		basic_bin_copy(tmp, data, sizeof(datatype), 0); \
		*(ptr + index) = tmp; \
	} \

#define ARRAY_SET_CLASS(datatype) \
	if(basic_strcmp(self->name, #datatype)) { \
		datatype* tmp = data; \
		*(ptr + index) = tmp->o_IF->clone(data); \
	} \

#define ARRAY_CMP_PRIMITIVE(datatype) \
	if(basic_strcmp(self->name, #datatype)) { \
		datatype* tmp; \
		datatype* tmp1; \
		for (size_t i = 0; i < Array_length(this); ++i) { \
			tmp = Array_get(this, i); \
			tmp1 = Array_get(this1, i); \
			if(!tmp) return false; \
			if(!tmp1) return false; \
			if (*tmp != *tmp1) return false; \
			} \
		return true; \
	} \

#define ARRAY_CMP_CLASS(datatype) \
	if(basic_strcmp(self->name, #datatype)) { \
		datatype* tmp; \
		datatype* tmp1; \
		for (size_t i = 0; i < Array_length(this); ++i) { \
			tmp = Array_get(this, i); \
			tmp1 = Array_get(this1, i); \
			if(!tmp) return false; \
			if(!tmp1) return false; \
			if (!tmp->o_IF->equals(tmp, tmp1)) return false; \
		} \
		return true; \
	} \

/* function prototypes */
/* overriding methods */ 
private_fun char* Array_toString(void* obj);
private_fun void* Array_clone(void* obj);
private_fun void Array_dtor(void* obj);
private_fun boolean Array_equals(void* obj, void* obj2);

/* methods */
private_fun void* Array_get(void* obj, size_t index);
private_fun void Array_set(void* obj, void* data, size_t index);
private_fun void Array_resize(void* obj, size_t new_length);
private_fun size_t Array_length(void* obj);
private_fun void Array_fill(void* obj, void* data);

/* public functions */

Array* Array_ctor(const char* name, size_t length)
{
	if (length < 0) return NULL;
	if (!name) return NULL;
	if (!basic_isAllowedType(name)) return NULL;

	BASIC_CTOR(Array);
	super->o_IF->clone = &Array_clone;
	super->o_IF->toString = &Array_toString;
	super->o_IF->dtor = &Array_dtor;
	super->o_IF->equals = &Array_equals;

	thisIF->get = &Array_get;
	thisIF->set = &Array_set;
	thisIF->length = &Array_length;
	thisIF->resize = &Array_resize;
	thisIF->fill = &Array_fill;

	self->sub = NULL;
	self->length = length;

	void** data;
	_MALLOC(void*, length, data);
	self->arr = data;
	self->name = basic_strcpy(name);
	return this;
}

/* array methods */

/* overriding object methods */
private_fun char* Array_toString(void* obj)
{
	CAST(Array, obj, NULL, );
	CAST_OBJECT(this->super, false, 1);
	_FREE(self1->toString);
	char* tmp;
	_MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	snprintf(tmp, 100, "This array contains: %zu '%s's", self->length, self->name);
	self1->toString = basic_strcpy(tmp);
	_FREE(tmp);
	return self1->toString;
}

private_fun void Array_dtor(void* obj)
{
	CAST(Array, obj, , );
	void** ptr = self->arr;

	for (size_t i = 0; i < this->_ArrayIF->length(obj); ++i) {
		if (basic_strcmp(self->name, "String")) {
			delete(*(ptr + i));
		}
		//primitive types
		else {
			_FREE(*(ptr + i));
			continue;
		}
	}
	_FREE(self->name);
	_FREE(self->arr);
	_FREE(self);

	_FREE(this->_ArrayIF);
	Object_dtor(this->super);
	FREE(this);
}

private_fun void* Array_clone(void* obj)
{
	CAST(Array, obj, NULL, );
	Array* clone = Array_ctor(self->name, self->length);
	for (size_t i = 0; i < self->length; ++i) {
		clone->_ArrayIF->set(clone, this->_ArrayIF->get(this, i), i);
	}
	return clone;
}

private_fun boolean Array_equals(void* obj, void* obj2)
{
	CAST(Array, obj, false, );
	CAST(Array, obj, false, 1);

	if (!basic_strcmp(self->name, self1->name)) return false;
	if (Array_length(self) != Array_length(self1)) return false;

	ARRAY_CMP_PRIMITIVE(double);
	ARRAY_CMP_PRIMITIVE(float);
	ARRAY_CMP_PRIMITIVE(char);
	ARRAY_CMP_PRIMITIVE(int);
	ARRAY_CMP_PRIMITIVE(boolean);
	ARRAY_CMP_PRIMITIVE(size_t);

	ARRAY_CMP_CLASS(String);

	return false;
}

/* array only methods */
private_fun void* Array_get(void* obj, size_t index)
{
	CAST(Array, obj, NULL, );
	if (index < 0) return NULL;
	void** ptr = self->arr;
	if (index >= self->length) return NULL;
	return *(ptr + index);
}

private_fun void Array_set(void* obj, void* data, size_t index)
{
	if (!data) return;
	if (index < 0) return;
	CAST(Array, obj, , );
	if (index >= self->length) return;
	void** ptr = self->arr;

	ARRAY_SET_PRIMITIVE(double);
	ARRAY_SET_PRIMITIVE(float);
	ARRAY_SET_PRIMITIVE(char);
	ARRAY_SET_PRIMITIVE(int);
	ARRAY_SET_PRIMITIVE(boolean);
	ARRAY_SET_PRIMITIVE(size_t);

	ARRAY_SET_CLASS(String);

}

private_fun void Array_fill(void* obj, void* data)
{
	CAST(Array, obj, , );
	if (!data) return;
	void** ptr = self->arr;
	for (size_t index = 0; index < self->length; ++index) {
		ARRAY_SET_PRIMITIVE(double);
		ARRAY_SET_PRIMITIVE(float);
		ARRAY_SET_PRIMITIVE(char);
		ARRAY_SET_PRIMITIVE(int);
		ARRAY_SET_PRIMITIVE(boolean);
		ARRAY_SET_PRIMITIVE(size_t);

		ARRAY_SET_CLASS(String);
	}
}

private_fun size_t Array_length(void* obj)
{
	CAST(Array, obj, 0, );
	return self->length;
}

private_fun void Array_resize(void* obj, size_t new_length)
{
	CAST(Array, obj, , );
	if (new_length <= 0) return;
	void** ptr = self->arr;
	if (new_length < self->length) {
		for (size_t i = new_length; i < self->length; ++i) {
			if (basic_strcmp(self->name, "String")) {
				delete(*(ptr + i));
			}
			//primitive types
			else {
				_FREE(*(ptr + i));
				continue;
			}
		}
	}
	_REALLOC(void*, new_length, ptr);
	self->length = new_length;
}
