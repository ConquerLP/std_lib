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
#define ARRAY_SET_PRIMITIVE(data_type) \
	data_type* tmp; \
	_MALLOC(data_type, 1, tmp); \
	basic_bin_copy(tmp, data, sizeof(data_type), 0); \
	*(ptr + index) = tmp; \

#define ARRAY_SET_CLASS(data_type) \
	data_type* tmp = NULL; \
	if (!def_hashtable_is_object(DEF_GLOBAL_HASHTABLE, data)) { \
		switch (self->type) { \
			case DEF_STRING: {tmp = String_ctor(data); break; } \
			default: tmp = NULL; \
		} \
		if (!tmp) def_critical_error("Array, tried to assign invalid class"); \
		else *(ptr + index) = tmp->o_IF->clone(data); \
	} \
	else tmp = data; \
	*(ptr + index) = tmp->o_IF->clone(data); \

#define ARRAY_CMP_PRIMITIVE(data_type) \
	data_type* tmp; \
	data_type* tmp1; \
	for (size_t i = 0; i < Array_length(this); ++i) { \
		tmp = Array_get(this, i); \
		tmp1 = Array_get(this1, i); \
		if (!tmp) return false; \
		if (!tmp1) return false; \
		if (*tmp != *tmp1) return false; \
		} \
	return true; \

#define ARRAY_CMP_CLASS(data_type) \
	data_type* tmp; \
	data_type* tmp1; \
	for (size_t i = 0; i < Array_length(this); ++i) { \
		tmp = Array_get(this, i); \
		tmp1 = Array_get(this1, i); \
		if (!tmp) return false; \
		if (!tmp1) return false; \
		if (!tmp->o_IF->equals(tmp, tmp1)) return false; \
	} \
	return true; \

#define ARRAY_APPEND_STRING_PRIMITIVE(data_type, func) \
	String* tmp1 = func(*((data_type*)Array_get(obj, i))); \
	tmp->_StringIF->append(tmp, "#"); \
	String* tmp2 = String_size_tToString(i); \
	tmp->_StringIF->append(tmp, tmp2); \
	tmp->_StringIF->append(tmp, ": "); \
	tmp->_StringIF->append(tmp, tmp1); \
	tmp->_StringIF->append(tmp, "\n"); \
	delete(tmp1); \
	delete(tmp2); \


#define ARRAY_APPEND_STRING_CLASS(data_type) \
	data_type* ptr = Array_get(obj, i); \
	char* to_string = ptr->o_IF->toString(ptr); \
	String* tmp1 = String_ctor(to_string); \
	tmp->_StringIF->append(tmp, "#"); \
	String* tmp2 = String_size_tToString(i + 1); \
	tmp->_StringIF->append(tmp, tmp2); \
	tmp->_StringIF->append(tmp, ": "); \
	tmp->_StringIF->append(tmp, tmp1); \
	tmp->_StringIF->append(tmp, "\n"); \
	delete(tmp1); \
	delete(tmp2); \

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

Array* Array_ctor(size_t data_type, size_t length)
{
	if (length < 0 || !basic_isAllowedType(data_type)) def_critical_error("Could not create new Array");
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
	self->type = data_type;

	void** data;
	_MALLOC(void*, length, data);
	for (size_t i = 0; i < length; ++i) {
		*(data + i) = NULL;
	}
	self->arr = data;
	return this;
}

/* array methods */

/* overriding object methods */
private_fun char* Array_toString(void* obj)
{
	CAST(Array, obj, NULL, );
	CAST_OBJECT(this->super, NULL, 1);
	_FREE(self1->toString);
	String* tmp = String_ctor("\Array contains:\n");
	for (size_t i = 0; i < self->length; ++i) {
		switch (self->type) {
		case DEF_BOOLEAN:		{ ARRAY_APPEND_STRING_PRIMITIVE(boolean, String_booleanToString); break;			  }
		case DEF_USHORT:		{ ARRAY_APPEND_STRING_PRIMITIVE(unsigned short, String_ushortToString); break;	  }
		case DEF_SHORT:			{ ARRAY_APPEND_STRING_PRIMITIVE(short, String_shortToString); break;			  }
		case DEF_CHAR:			{ ARRAY_APPEND_STRING_PRIMITIVE(char, String_charToString); break;			  }
		case DEF_UINT:			{ ARRAY_APPEND_STRING_PRIMITIVE(unsigned int, String_uintToString); break;	  }
		case DEF_INT:			{ ARRAY_APPEND_STRING_PRIMITIVE(int, String_intToString); break;				  }
		case DEF_ULONGINT:		{ ARRAY_APPEND_STRING_PRIMITIVE(unsigned long int, String_ulongintToString); break; }
		case DEF_LONGINT:		{ ARRAY_APPEND_STRING_PRIMITIVE(long int, String_longintToString); break; }
		case DEF_LONGLONGINT:	{ ARRAY_APPEND_STRING_PRIMITIVE(long long int, String_longlongintToString); break; }
		case DEF_SIZE_T:		{ ARRAY_APPEND_STRING_PRIMITIVE(size_t, String_size_tToString); break;			  }
		case DEF_FLOAT:			{ ARRAY_APPEND_STRING_PRIMITIVE(float, String_floatToString); break;			  }
		case DEF_DOUBLE:		{ ARRAY_APPEND_STRING_PRIMITIVE(double, String_doubleToString); break;			  }
		case DEF_LONGDOUBLE:	{ ARRAY_APPEND_STRING_PRIMITIVE(long double, String_longdoubleToString); break;		  }
		case DEF_STRING:		{ ARRAY_APPEND_STRING_CLASS(String); break;										  }
		}
	}
	CAST(String, tmp, NULL, 2);
	self1->toString = basic_strcpy(self2->str);
	delete(tmp);
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
			case DEF_UINT: _FREE(*(ptr + i)); break;
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
	CAST(Array, obj2, false, 1);
	if (self->type != self1->type) return false;
	if (Array_length(self) != Array_length(self1)) return false;
	switch (self->type) {
		case DEF_BOOLEAN:		{ ARRAY_CMP_PRIMITIVE(boolean);}
		case DEF_USHORT:		{ ARRAY_CMP_PRIMITIVE(unsigned short);}
		case DEF_SHORT:			{ ARRAY_CMP_PRIMITIVE(short);}
		case DEF_CHAR:			{ ARRAY_CMP_PRIMITIVE(char);}
		case DEF_UINT:			{ ARRAY_CMP_PRIMITIVE(unsigned int);}
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
	if (index >= self->length) return NULL;
	void** ptr = self->arr;
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
		case DEF_UINT:			{ ARRAY_SET_PRIMITIVE(unsigned int); break;		}
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
			case DEF_UINT:			{ ARRAY_SET_PRIMITIVE(unsigned int); break;		}
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
				case DEF_UINT: _FREE(*(ptr + i)); break;
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
