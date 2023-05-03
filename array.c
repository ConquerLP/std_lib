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

/* function prototypes */
private_fun char* Array_toString(void* obj);
private_fun void* Array_clone(void* obj);
private_fun void Array_dtor(void* array);

private_fun void* Array_get(void* obj, size_t index);
private_fun void Array_set(void* obj, void* data, size_t index);
private_fun size_t Array_length(void* obj);


/* public functions */

Array* Array_ctor(const char* name, size_t length)
{
	if (length <= 0) return NULL;
	if (!name) return NULL;
	if (!basic_isAllowedType(name)) return NULL;
	Object* super = Object_ctor("Array");

	Array* this;
	ArrayIF* thisIF;
	o_Array* self;
	MALLOC(Array, 1, this);
	MALLOC(ArrayIF, 1, thisIF);
	MALLOC(o_Array, 1, self);

	this->self = self;
	this->arrayIF = thisIF;

	thisIF->get = &Array_get;
	thisIF->set = &Array_set;
	thisIF->length = &Array_length;

	this->objectIF = super->objectIF;

	super->objectIF->clone = &Array_clone;
	super->objectIF->toString = &Array_toString;
	super->objectIF->dtor = &Array_dtor;

	this->super = super;
	self->sub = NULL;
	self->length = length;

	void** data;
	MALLOC(void*, length, data);
	self->arr = data;
	self->name = basic_strcpy(name);
	self->toString = basic_strcpy("");
	return this;
}

/* array methods */

/* overriding object methods */
private_fun char* Array_toString(void* obj)
{
	if (!obj) return NULL;
	Array* this = obj;
	o_Array* self = this->self;
	FREE(self->toString);
	char* tmp;
	MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	snprintf(tmp, 100, "This array contains: %zu '%s's", self->length, self->name);
	self->toString = basic_strcpy(tmp);
	FREE(tmp);
	return self->toString;
}

private_fun void Array_dtor(void* array)
{
	if (!array) return;
	Array* this = array;
	o_Array* self = this->self;
	void** ptr = self->arr;

	for (size_t i = 0; i < this->arrayIF->length(array); ++i) {
		if (basic_strcmp(self->name, "String")) {
			delete(*(ptr + i));
		}
		//primitive types
		else {
			FREE(*(ptr + i));
			continue;
		}
	}
	FREE(self->toString);
	FREE(self->name);
	FREE(self->arr);
	FREE(self);

	FREE(this->arrayIF);
	Object* tmp = Object_ctor("");
	tmp->objectIF->dtor(this->super);
	tmp->objectIF->dtor(tmp);
	FREE(this);
}

private_fun void* Array_clone(void* obj)
{
	if (!obj) return NULL;
	Array* this = obj;
	o_Array* self = this->self;
	Array* clone = Array_ctor(self->name, self->length);
	for (size_t i = 0; i < self->length; ++i) {
		clone->arrayIF->set(clone, this->arrayIF->get(this, i), i);
	}
	return clone;
}

/* array only methods */
private_fun void* Array_get(void* arr, size_t index)
{
	if (!arr) return NULL;
	if (index < 0) return NULL;
	Array* this = arr;
	o_Array* self = this->self;
	void** ptr = self->arr;
	if (index >= self->length) return NULL;
	return *(ptr + index);
}

private_fun void Array_set(void* arr, void* data, size_t index)
{
	if (!arr) return;
	if (!data) return;
	if (index < 0) return;
	Array* this = arr;
	o_Array* self = this->self;
	if (index >= self->length) return;
	void** ptr = self->arr;
	if (basic_strcmp(self->name, "double")) {
		double* tmp;
		MALLOC(double, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(double), 0);
		*(ptr + index) = tmp;
		return;
	}
	if (basic_strcmp(self->name, "float")) {
		float* tmp;
		MALLOC(float, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(float), 0);
		*(ptr + index) = tmp;
		return;
	}
	if (basic_strcmp(self->name, "char")) {
		char* tmp;
		MALLOC(char, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(char), 0);
		*(ptr + index) = tmp;
		return;
	}
	if (basic_strcmp(self->name, "int")) {
		int* tmp;
		MALLOC(int, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(int), 0);
		*(ptr + index) = tmp;
		return;
	}
	if (basic_strcmp(self->name, "size_t")) {
		size_t* tmp;
		MALLOC(size_t, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(size_t), 0);
		*(ptr + index) = tmp;
		return;
	}
	if (basic_strcmp(self->name, "String")) {
		String* str = data;
		*(ptr + index) = str->objectIF->clone(data);
		return;
	}
}

private_fun size_t Array_length(void* obj)
{
	if (!obj) return 0;
	o_Array* this = ((Array*)obj)->self;
	return this->length;
}