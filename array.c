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
	datatype* tmp; \
	_MALLOC(datatype, 1, tmp); \
	basic_bin_copy(tmp, data, sizeof(datatype), 0); \
	*(ptr + index) = tmp; \

#define ARRAY_SET_CLASS(datatype) \
	datatype* tmp = data; \
	*(ptr + index) = tmp->o_IF->clone(data); \

#define ARRAY_CMP_PRIMITIVE(datatype) \
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

#define ARRAY_CMP_CLASS(datatype) \
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

Array* Array_ctor(size_t datatype, size_t length)
{
	if (length < 0) return NULL;
	if (!basic_isAllowedType(datatype)) return NULL;
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
	self->type = datatype;

	void** data;
	_MALLOC(void*, length, data);
	self->arr = data;
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
	String* str = String_ctor("");
	CAST(String, str, NULL, 2);
	//snprintf(tmp, 100, "This array contains: %zu '%s's.\n", self->length, basic_BATAL_to_string(self->type));
	str->_StringIF->append(str, tmp);
	for (size_t i = 0; i < self->length; ++i) {
		switch (self->type) {
			/*
			case DATAL_INT:
				snprintf(tmp, 100, "Value(%zu): %i\n", i, *((int*)Array_get(obj, i)));
				break;
			case DATAL_FLOAT:
				snprintf(tmp, 100, "Value(%zu): %f\n", i, *((float*)Array_get(obj, i)));
				break;
			case DATAL_DOUBLE:
				snprintf(tmp, 100, "Value(%zu): %lf\n", i, *((double*)Array_get(obj, i)));
				break;
			case DATAL_SIZE_T: 
				snprintf(tmp, 100, "Value(%zu): %zu\n", i, *((size_t*)Array_get(obj, i)));
				break;
			default: 
				break;
				*/
		}
		str->_StringIF->append(str, tmp);
	}
	self1->toString = basic_strcpy(self2->str);
	delete(str);
	_FREE(tmp);
	return self1->toString;
}

private_fun void Array_dtor(void* obj)
{
	CAST(Array, obj, , );
	void** ptr = self->arr;
	for (size_t i = 0; i < this->_ArrayIF->length(obj); ++i) {
		switch (self->type) {
			case DEF_BOOLEAN: _FREE(*(ptr + i)); break; 
			case DEF_USHORT: _FREE(*(ptr + i)); break;
			case DEF_SHORT: _FREE(*(ptr + i)); break;
			case DEF_CHAR: _FREE(*(ptr + i)); break;
			case DEF_DEF_UINT: _FREE(*(ptr + i)); break;
			case DEF_INT: _FREE(*(ptr + i)); break;
			case DEF_ULONGINT: _FREE(*(ptr + i)); break;
			case DEF_LONGINT: _FREE(*(ptr + i)); break;
			case DEF_LONGLONGINT: _FREE(*(ptr + i)); break;
			case DEF_SIZE_T: _FREE(*(ptr + i)); break;
			case DEF_FLOAT: _FREE(*(ptr + i)); break;
			case DEF_DOUBLE: _FREE(*(ptr + i)); break;
			case DEF_LONGDOUBLE: _FREE(*(ptr + i)); break;
			case DEF_STRING: delete(*(ptr + i)); break;
			default: break;
		}
	}
	_FREE(self->arr);
	_FREE(self);
	_FREE(this->_ArrayIF);
	Object_dtor(this->super);
	FREE(this);
}

private_fun void* Array_clone(void* obj)
{
	CAST(Array, obj, NULL, );
	Array* clone = Array_ctor(self->type, self->length);
	for (size_t i = 0; i < self->length; ++i) {
		clone->_ArrayIF->set(clone, this->_ArrayIF->get(this, i), i);
	}
	return clone;
}

private_fun boolean Array_equals(void* obj, void* obj2)
{
	CAST(Array, obj, false, );
	CAST(Array, obj, false, 1);
	if (self->type != self1->type) return false;
	if (Array_length(self) != Array_length(self1)) return false;
	switch (self->type) {
		case DEF_BOOLEAN:		{ ARRAY_CMP_PRIMITIVE(boolean);}
		case DEF_USHORT:		{ ARRAY_CMP_PRIMITIVE(unsigned short);}
		case DEF_SHORT:			{ ARRAY_CMP_PRIMITIVE(short);}
		case DEF_CHAR:			{ ARRAY_CMP_PRIMITIVE(char);}
		case DEF_DEF_UINT:		{ ARRAY_CMP_PRIMITIVE(unsigned int);}
		case DEF_INT:			{ ARRAY_CMP_PRIMITIVE(int);}
		case DEF_ULONGINT:		{ ARRAY_CMP_PRIMITIVE(unsigned long int);}
		case DEF_LONGINT:		{ ARRAY_CMP_PRIMITIVE(long int);}
		case DEF_LONGLONGINT:	{ ARRAY_CMP_PRIMITIVE(long long int);}
		case DEF_SIZE_T:		{ ARRAY_CMP_PRIMITIVE(size_t);}
		case DEF_FLOAT:			{ ARRAY_CMP_PRIMITIVE(float);}
		case DEF_DOUBLE:		{ ARRAY_CMP_PRIMITIVE(double);}
		case DEF_LONGDOUBLE:	{ ARRAY_CMP_PRIMITIVE(long double);}
		case DEF_STRING:		{ ARRAY_CMP_CLASS(String);}
		default:				return false;
	}
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
	switch (self->type) {
		case DEF_BOOLEAN:		{ ARRAY_SET_PRIMITIVE(boolean); break;			}
		case DEF_USHORT:		{ ARRAY_SET_PRIMITIVE(unsigned short); break;	}
		case DEF_SHORT:			{ ARRAY_SET_PRIMITIVE(short); break;			}
		case DEF_CHAR:			{ ARRAY_SET_PRIMITIVE(char); break;				}
		case DEF_DEF_UINT:		{ ARRAY_SET_PRIMITIVE(unsigned int); break;		}
		case DEF_INT:			{ ARRAY_SET_PRIMITIVE(int); break;				}
		case DEF_ULONGINT:		{ ARRAY_SET_PRIMITIVE(unsigned long int); break;}
		case DEF_LONGINT:		{ ARRAY_SET_PRIMITIVE(long int); break;			}
		case DEF_LONGLONGINT:	{ ARRAY_SET_PRIMITIVE(long long int); break;	}
		case DEF_SIZE_T:		{ ARRAY_SET_PRIMITIVE(size_t); break;			}
		case DEF_FLOAT:			{ ARRAY_SET_PRIMITIVE(float); break;			}
		case DEF_DOUBLE:		{ ARRAY_SET_PRIMITIVE(double); break;			}
		case DEF_LONGDOUBLE:	{ ARRAY_SET_PRIMITIVE(long double); break;		}
		case DEF_STRING:		{ ARRAY_SET_CLASS(String); break;				}
		default: break;
	}
}

private_fun void Array_fill(void* obj, void* data)
{
	CAST(Array, obj, , );
	if (!data) return;
	void** ptr = self->arr;
	for (size_t index = 0; index < self->length; ++index) {
		switch (self->type) {
			case DEF_BOOLEAN:		{ ARRAY_SET_PRIMITIVE(boolean); break;			}
			case DEF_USHORT:		{ ARRAY_SET_PRIMITIVE(unsigned short); break;	}
			case DEF_SHORT:			{ ARRAY_SET_PRIMITIVE(short); break;			}
			case DEF_CHAR:			{ ARRAY_SET_PRIMITIVE(char); break;				}
			case DEF_DEF_UINT:		{ ARRAY_SET_PRIMITIVE(unsigned int); break;		}
			case DEF_INT:			{ ARRAY_SET_PRIMITIVE(int); break;				}
			case DEF_ULONGINT:		{ ARRAY_SET_PRIMITIVE(unsigned long int); break;}
			case DEF_LONGINT:		{ ARRAY_SET_PRIMITIVE(long int); break;			}
			case DEF_LONGLONGINT:	{ ARRAY_SET_PRIMITIVE(long long int); break;	}
			case DEF_SIZE_T:		{ ARRAY_SET_PRIMITIVE(size_t); break;			}
			case DEF_FLOAT:			{ ARRAY_SET_PRIMITIVE(float); break;			}
			case DEF_DOUBLE:		{ ARRAY_SET_PRIMITIVE(double); break;			}
			case DEF_LONGDOUBLE:	{ ARRAY_SET_PRIMITIVE(long double); break;		}
			case DEF_STRING:		{ ARRAY_SET_CLASS(String); break;				}
			default: break;
		}
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
			switch (self->type) {
				case DEF_BOOLEAN: _FREE(*(ptr + i)); break;
				case DEF_USHORT: _FREE(*(ptr + i)); break;
				case DEF_SHORT: _FREE(*(ptr + i)); break;
				case DEF_CHAR: _FREE(*(ptr + i)); break;
				case DEF_DEF_UINT: _FREE(*(ptr + i)); break;
				case DEF_INT: _FREE(*(ptr + i)); break;
				case DEF_ULONGINT: _FREE(*(ptr + i)); break;
				case DEF_LONGINT: _FREE(*(ptr + i)); break;
				case DEF_LONGLONGINT: _FREE(*(ptr + i)); break;
				case DEF_SIZE_T: _FREE(*(ptr + i)); break;
				case DEF_FLOAT: _FREE(*(ptr + i)); break;
				case DEF_DOUBLE: _FREE(*(ptr + i)); break;
				case DEF_LONGDOUBLE: _FREE(*(ptr + i)); break;
				case DEF_STRING: delete(*(ptr + i)); break;
				default: break;
			}
		}
	}
	_REALLOC(void*, new_length, ptr);
	self->length = new_length;
}
