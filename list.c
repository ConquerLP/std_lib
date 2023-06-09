#include "list.h"
#include "list.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

#include "string.h"
#include "string.r"

#include <stdlib.h>

/* MACROS */
#define LIST_COMPARE_ELEMENT(data_type) \
	data_type* a = NULL; \
	data_type* b = NULL; \
	for (size_t i = 0; i < self->length; ++i) { \
		a = List_get(this, i); \
		b = List_get(this1, i); \
		if (!a) return false; \
		if (!b) return false; \
		if (*a != *b) return false; \
	} \
	return true; \

#define LIST_COMPARE_ELEMENT_CLASS(data_type) \
	data_type* a = NULL; \
	data_type* b = NULL; \
	for (size_t i = 0; i < self->length; ++i) { \
		a = List_get(this, i); \
		b = List_get(this, i); \
		if (!a) return false; \
		if (!b) return false; \
		if (!a->o_IF->equals(a, b)) return false; \
	} \
	return true; \

#define LIST_SET_ELEMENT(data_type) \
	if (def_hashtable_is_object(DEF_GLOBAL_HASHTABLE, data)) def_critical_error("List, tried to assign class but expected primitive datatype"); \
	data_type* tmp; \
	_MALLOC(data_type, 1, tmp); \
	basic_bin_copy(tmp, data, sizeof(data_type), 0); \
	node->data = tmp; \
	return; \

#define LIST_SET_ELEMENT_CLASS(data_type) \
	data_type* ptr = NULL; \
	if (!def_hashtable_is_object(DEF_GLOBAL_HASHTABLE, data)) { \
		switch (self->type) { \
			case DEF_STRING: {ptr = String_ctor(data); break; } \
			default: ptr = NULL; \
		} \
		if (!ptr) def_critical_error("List, tried to assign unsupported class"); \
		else node->data = ptr->o_IF->clone(data); \
	} \
	else ptr = data; \
	node->data = ptr->o_IF->clone(data); \
	return; \

#define LIST_APPEND_STRING_PRIMITIVE(data_type, func) \
	String* tmp1 = func(*((data_type*)List_get(obj, i))); \
	tmp->_StringIF->append(tmp, "#"); \
	String* tmp2 = String_size_tToString(i); \
	tmp->_StringIF->append(tmp, tmp2); \
	tmp->_StringIF->append(tmp, ": "); \
	tmp->_StringIF->append(tmp, tmp1); \
	tmp->_StringIF->append(tmp, "\n"); \
	delete(tmp1); \
	delete(tmp2); \

#define LIST_APPEND_STRING_CLASS(data_type) \
	data_type* ptr = List_get(obj, i); \
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
private_fun char* List_toString(void* obj);
private_fun void List_dtor(void* obj);
private_fun void* List_clone(void* obj);
private_fun boolean List_equals(void* obj, void* obj2);
/* methods */
private_fun void* List_get(void* obj, size_t index);
private_fun void List_set(void* obj, void* data, size_t index);
private_fun void List_append(void* obj, void* data);
private_fun void List_clear(void* obj);
private_fun void List_insert(void* obj, void* data, size_t index);
private_fun void List_delete(void* obj, size_t index);
private_fun size_t List_find(void* obj, void* toFind);
private_fun void List_addAll(void* obj, void* listToAdd);
private_fun boolean List_isEmpty(void* obj);
private_fun size_t List_size(void* obj);
private_fun List* List_subList(void* obj, size_t start, size_t end);
private_fun Array* List_toArray(void* obj);

/* helper functions */
private_fun Node* List_getNode(List* this, size_t index);


/* public functions */
List* List_ctor(size_t data_type)
{
	if (!basic_isAllowedType(data_type)) return NULL;
	BASIC_CTOR(List);
	super->o_IF->clone = &List_clone;
	super->o_IF->dtor = &List_dtor;
	super->o_IF->toString = &List_toString;
	super->o_IF->equals = &List_equals;

	thisIF->get = &List_get;
	thisIF->set = &List_set;
	thisIF->append = &List_append;
	thisIF->clear = &List_clear;
	thisIF->insert = &List_insert;
	thisIF->delete = &List_delete;
	thisIF->find = &List_find;
	thisIF->addAll = &List_addAll;
	thisIF->isEmpty = &List_isEmpty;
	thisIF->size = &List_size;
	thisIF->subList = &List_subList;
	thisIF->toArray = &List_toArray;

	self->sub = NULL;
	self->length = 0;
	self->head = NULL;
	self->tail = NULL;
	self->type = data_type;
	return this;
}

/* List methods */

/* overriding object methods */
private_fun char* List_toString(void* obj)
{
	CAST(List, obj, NULL, );
	CAST_OBJECT(this->super, NULL, 1);
	_FREE(self1->toString);
	String* tmp = String_ctor("\nList contains:\n");
	for (size_t i = 0; i < self->length; ++i) {
		switch (self->type) {
			case DEF_BOOLEAN:		{ LIST_APPEND_STRING_PRIMITIVE(boolean, String_booleanToString); break;			  }
			case DEF_USHORT:		{ LIST_APPEND_STRING_PRIMITIVE(unsigned short, String_ushortToString); break;	  }
			case DEF_SHORT:			{ LIST_APPEND_STRING_PRIMITIVE(short, String_shortToString); break;			  }
			case DEF_CHAR:			{ LIST_APPEND_STRING_PRIMITIVE(char, String_charToString); break;			  }
			case DEF_UINT:			{ LIST_APPEND_STRING_PRIMITIVE(unsigned int, String_uintToString); break;	  }
			case DEF_INT:			{ LIST_APPEND_STRING_PRIMITIVE(int, String_intToString); break;				  }
			case DEF_ULONGINT:		{ LIST_APPEND_STRING_PRIMITIVE(unsigned long int, String_ulongintToString); break; }
			case DEF_LONGINT:		{ LIST_APPEND_STRING_PRIMITIVE(long int, String_longintToString); break; }
			case DEF_LONGLONGINT:	{ LIST_APPEND_STRING_PRIMITIVE(long long int, String_longlongintToString); break; }
			case DEF_SIZE_T:		{ LIST_APPEND_STRING_PRIMITIVE(size_t, String_size_tToString); break;			  }
			case DEF_FLOAT:			{ LIST_APPEND_STRING_PRIMITIVE(float, String_floatToString); break;			  }
			case DEF_DOUBLE:		{ LIST_APPEND_STRING_PRIMITIVE(double, String_doubleToString); break;			  }
			case DEF_LONGDOUBLE:	{ LIST_APPEND_STRING_PRIMITIVE(long double, String_longdoubleToString); break;		  }
			case DEF_STRING:		{ LIST_APPEND_STRING_CLASS(String); break;										  }
		}
	}
	CAST(String, tmp, NULL, 2);
	self1->toString = basic_strcpy(self2->str);
	delete(tmp);
	return self1->toString;
}

private_fun void List_dtor(void* obj)
{
	CAST(List, obj, , );
	List_clear(obj);
	self->head = NULL;
	self->tail = NULL;
	self->sub = NULL;
	_FREE(self);

	_FREE(this->_ListIF);
	this->self = NULL;
	Object_dtor(this->super);
	FREE(this);
}

private_fun void* List_clone(void* obj)
{
	CAST(List, obj, NULL, );
	List* clone = List_ctor(self->type);
	if (!clone) return NULL;
	List_addAll(clone, this);
	return clone;
}

private_fun boolean List_equals(void* obj, void* obj2)
{
	CAST(List, obj, false, );
	CAST(List, obj2, false, 1);
	if (self->type != self1->type) return false;
	if (List_size(self) != List_size(self1)) return false;
	switch (self->type) {
		case DEF_BOOLEAN:		{ LIST_COMPARE_ELEMENT(boolean); 		  }
		case DEF_USHORT:		{ LIST_COMPARE_ELEMENT(unsigned short);	  }
		case DEF_SHORT:			{ LIST_COMPARE_ELEMENT(short);			  }
		case DEF_CHAR:			{ LIST_COMPARE_ELEMENT(char);			  }
		case DEF_UINT:			{ LIST_COMPARE_ELEMENT(unsigned int);	  }
		case DEF_INT:			{ LIST_COMPARE_ELEMENT(int);			  }
		case DEF_ULONGINT:		{ LIST_COMPARE_ELEMENT(unsigned long int);}
		case DEF_LONGINT:		{ LIST_COMPARE_ELEMENT(long int);		  }
		case DEF_LONGLONGINT:	{ LIST_COMPARE_ELEMENT(long long int);	  }
		case DEF_SIZE_T:		{ LIST_COMPARE_ELEMENT(size_t);			  }
		case DEF_FLOAT:			{ LIST_COMPARE_ELEMENT(float);			  }
		case DEF_DOUBLE:		{ LIST_COMPARE_ELEMENT(double);			  }
		case DEF_LONGDOUBLE:	{ LIST_COMPARE_ELEMENT(long double);	  }
		case DEF_STRING:		{ LIST_COMPARE_ELEMENT_CLASS(String);	  }
		default:				{ return false;							  }
	}
}

/* List only methods */
private_fun void* List_get(void* obj, size_t index)
{
	CAST(List, obj, NULL, );
	return List_getNode(this, index)->data;
}

private_fun void List_set(void* obj, void* data, size_t index)
{
	if (!data) return;
	CAST(List, obj, , );
	Node* node = List_getNode(this, index);
	if (!node) return;
	switch (self->type) {
		case DEF_BOOLEAN:		{ LIST_SET_ELEMENT(boolean);		  }
		case DEF_USHORT:		{ LIST_SET_ELEMENT(unsigned short);	  }
		case DEF_SHORT:			{ LIST_SET_ELEMENT(short);			  }
		case DEF_CHAR:			{ LIST_SET_ELEMENT(char);			  }
		case DEF_UINT:			{ LIST_SET_ELEMENT(unsigned int);	  }
		case DEF_INT:			{ LIST_SET_ELEMENT(int);			  }
		case DEF_ULONGINT:		{ LIST_SET_ELEMENT(unsigned long int);}
		case DEF_LONGINT:		{ LIST_SET_ELEMENT(long int);		  }
		case DEF_LONGLONGINT:	{ LIST_SET_ELEMENT(long long int);	  }
		case DEF_SIZE_T:		{ LIST_SET_ELEMENT(size_t);			  }
		case DEF_FLOAT:			{ LIST_SET_ELEMENT(float);			  }
		case DEF_DOUBLE:		{ LIST_SET_ELEMENT(double);			  }
		case DEF_LONGDOUBLE:	{ LIST_SET_ELEMENT(long double);	  }
		case DEF_STRING:		{ LIST_SET_ELEMENT_CLASS(String);	  }
		default:				{ return;							  }
	}
}

private_fun void List_append(void* obj, void* data)
{
	if (!data) return;
	CAST(List, obj, , );
	Node* node;
	_MALLOC(Node, 1, node);
	if (self->length == 0) {
		self->head = node;
		self->tail = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else {
		Node* tail = self->tail;
		tail->next = node;
		node->prev = tail;
		node->next = NULL;
		self->tail = node;
	}
	self->length++;
	List_set(obj, data, self->length - 1);
}

private_fun void List_clear(void* obj)
{
	CAST(List, obj, , );
	while (self->length != 0) {
		List_delete(obj, self->length);
	}
}

private_fun void List_insert(void* obj, void* data, size_t index)
{
	if (!data) return;
	CAST(List, obj, , );
	Node* node = List_getNode(this, index);
	if (!node) return;
	Node* new;
	_MALLOC(Node, 1, new);
	new->prev = node->prev;
	new->next = node;
	node->prev = new;
	self->length++;
	List_set(obj, data, index);
}

private_fun void List_delete(void* obj, size_t index)
{
	CAST(List, obj, , );
	Node* node = List_getNode(this, index);
	if (!node) return;
	switch (self->type) {
		case DEF_BOOLEAN: _FREE(node->data); break;
		case DEF_USHORT: _FREE(node->data); break;
		case DEF_SHORT: _FREE(node->data); break;
		case DEF_CHAR: _FREE(node->data); break;
		case DEF_UINT: _FREE(node->data); break;
		case DEF_INT: _FREE(node->data); break;
		case DEF_ULONGINT: _FREE(node->data); break;
		case DEF_LONGINT: _FREE(node->data); break;
		case DEF_LONGLONGINT: _FREE(node->data); break;
		case DEF_SIZE_T: _FREE(node->data); break;
		case DEF_FLOAT: _FREE(node->data); break;
		case DEF_DOUBLE: _FREE(node->data); break;
		case DEF_LONGDOUBLE: _FREE(node->data); break;
		case DEF_STRING: delete(node->data); break;
		default: return;
	}
	//rearrange the nodes, head, tail
	if (node->prev) {
		if (node->next) {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		else {
			node->prev->next = NULL;
			self->tail = node->prev;
		}
	}
	else {
		self->head = node->next;
		if (node->next) node->next->prev = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	_FREE(node);
	self->length--;
}

private_fun size_t List_find(void* obj, void* toFind)
{
	CAST(List, obj, -1, );
	if (!toFind) return -1;
	if (self->length == 0) return -1;
	Node* tmp = self->head;
	if (toFind == tmp->data) return 0;
	for (size_t i = 0; i < self->length; ++i) {
		if (tmp->data == toFind) return i;
	}
	return -1;
}

private_fun void List_addAll(void* obj, void* listToAdd)
{
	CAST(List, obj, , );
	CAST(List, listToAdd, , 1);
	if (self1->length == 0) return;
	if (self->type != self1->type) return;
	Node* tmp = self1->head;
	for (size_t i = 0; i < self1->length; ++i) {
		List_append(obj, tmp->data);
		tmp = tmp->next;
	}
}

private_fun boolean List_isEmpty(void* obj)
{
	CAST(List, obj, true, );
	if (self->length == 0) return true;
	else return false;
}

private_fun size_t List_size(void* obj)
{
	CAST(List, obj, 0, );
	return self->length;
}

private_fun List* List_subList(void* obj, size_t start, size_t end)
{
	CAST(List, obj, NULL, );
	if (start < 0) return NULL;
	if (start > end) return NULL;
	List* sub = List_ctor(self->type);
	if (end > self->length) end = self->length;
	if (start == end) {
		List_append(sub, List_get(obj, start));
	}
	else {
		for (size_t i = start; i < end; ++i) {
			List_append(sub, List_get(obj, i));
		}
	}
	return sub;
}

private_fun Array* List_toArray(void* obj)
{
	CAST(List, obj, NULL, );
	if (self->length == 0) return NULL;
	Array* arr = Array_ctor(self->type, self->length);
	for (size_t i = 0; i < self->length; ++i) {
		arr->_ArrayIF->set(arr, List_get(obj, i), i);
	}
	return arr;
}

/* helper functions */
private_fun Node* List_getNode(List* this, size_t index)
{
	if (!this) return NULL;
	if (index < 0) return NULL;
	o_List* self = this->self;
	if (self->length == 0) return NULL;
	if (index == 0) return self->head;
	if (index == self->length) return self->tail;
	if (index > self->length) return NULL;
	Node* tmp = self->head;
	for (size_t i = 0; i < index; ++i) {
		tmp = tmp->next;
	}
	return tmp;
}