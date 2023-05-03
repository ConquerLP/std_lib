#include "list.h"
#include "list.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

#include "string.h"
#include "string.r"

#include <stdlib.h>

/* function prototypes */
/* overriding methods */
private_fun char* List_toString(void* obj);
private_fun void List_dtor(void* obj);
private_fun void* List_clone(void* obj);
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

/* helper functions */
private_fun Node* List_getNode(List* this, size_t index);


/* public functions */
List* List_ctor(const char* name)
{
	if (!basic_isAllowedType(name)) return NULL;

	Object* super = Object_ctor("List");
	List* this;
	ListIF* thisIF;
	o_List* self;

	MALLOC(List, 1, this);
	MALLOC(ListIF, 1, thisIF);
	MALLOC(o_List, 1, self);

	this->self = self;
	this->listIF = thisIF;

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

	this->objectIF = super->objectIF;
	this->super = super;

	super->objectIF->clone = &List_clone;
	super->objectIF->dtor = &List_dtor;
	super->objectIF->toString = &List_toString;

	self->sub = NULL;
	self->length = 0;
	self->head = NULL;
	self->tail = NULL;
	self->name = basic_strcpy(name);
	self->toString = basic_strcpy("");

	return this;
}

/* List methods */

/* overriding object methods */
private_fun char* List_toString(void* obj)
{
	if (!obj) return NULL;
	List* this = obj;
	o_List* self = this->self;
	FREE(self->toString);
	char* tmp;
	MALLOC(char, 100, tmp);
	basic_memset(tmp, '\0', 100);
	snprintf(tmp, 100, "This List contains: %zu '%s's", self->length, self->name);
	self->toString = basic_strcpy(tmp);
	FREE(tmp);
	return self->toString;
}

private_fun void List_dtor(void* obj)
{
	if (!obj) return;
	List* this = obj;
	o_List* self = this->self;
	List_clear(obj);
	self->head = NULL;
	self->tail = NULL;
	FREE(self->name);
	FREE(self->toString);
	self->sub = NULL;
	FREE(self);

	FREE(this->listIF);
	this->self = NULL;
	Object_dtor(this->super);
	FREE(this);
}

private_fun void* List_clone(void* obj)
{
	if (!obj) return NULL;
	List* this = obj;
	o_List* self = this->self;
	List* clone = List_ctor(self->name);
	if (!clone) return NULL;
	List_addAll(clone, this);
	return clone;
}

/* List only methods */
private_fun void* List_get(void* obj, size_t index)
{
	if (!obj) return NULL;
	List* this = obj;
	return List_getNode(this, index)->data;
}

private_fun void List_set(void* obj, void* data, size_t index)
{
	if (!obj) return;
	if (!data) return;
	List* this = obj;
	Node* node = List_getNode(this, index);
	if (!node) return;
	o_List* self = this->self;
	if (basic_strcmp(self->name, "double")) {
		double* tmp;
		MALLOC(double, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(double), 0);
		node->data = tmp;
		return;
	}
	if (basic_strcmp(self->name, "float")) {
		float* tmp;
		MALLOC(float, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(float), 0);
		node->data = tmp;
		return;
	}
	if (basic_strcmp(self->name, "char")) {
		char* tmp;
		MALLOC(char, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(char), 0);
		node->data = tmp;
		return;
	}
	if (basic_strcmp(self->name, "int")) {
		int* tmp;
		MALLOC(int, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(int), 0);
		node->data = tmp;
		return;
	}
	if (basic_strcmp(self->name, "size_t")) {
		size_t* tmp;
		MALLOC(size_t, 1, tmp);
		basic_bin_copy(tmp, data, sizeof(size_t), 0);
		node->data = tmp;
		return;
	}	
	if (basic_strcmp(self->name, "String")) {
		String* str = data;
		node->data = str->objectIF->clone(data);
		return;
	}
}

private_fun void List_append(void* obj, void* data)
{
	if (!obj) return;
	if (!data) return;
	List* this = obj;
	o_List* self = this->self;
	Node* node;
	MALLOC(Node, 1, node);
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
	if (!obj) return;
	List* this = obj;
	o_List* self = this->self;
	while (self->length != 0) {
		List_delete(obj, self->length);
	}
}

private_fun void List_insert(void* obj, void* data, size_t index)
{
	if (!obj) return;
	if (!data) return;
	List* this = obj;
	o_List* self = this->self;
	Node* node = List_getNode(this, index);
	if (!node) return;
	Node* new;
	MALLOC(Node, 1, new);
	new->prev = node->prev;
	new->next = node;
	node->prev = new;
	self->length++;
	List_set(obj, data, index);
}

private_fun void List_delete(void* obj, size_t index)
{
	if (!obj) return;
	List* this = obj;
	Node* node = List_getNode(this, index);
	if (!node) return;
	o_List* self = this->self;
	//classes
	if (basic_strcmp(self->name, "String")) {
		delete(node->data);
	}
	//primitive types
	else {
		FREE(node->data);
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
		if(node->next) node->next->prev = NULL;
	}
	node->next = NULL;
	node->prev = NULL;
	FREE(node);
	self->length--;
}

private_fun size_t List_find(void* obj, void* toFind)
{
	if (!obj) return -1;
	if (!toFind) return -1;
	List* this = obj;
	o_List* self = this->self;
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
	if (!obj) return;
	if (!listToAdd) return;
	List* this = obj;
	o_List* self = this->self;
	List* list_add = listToAdd;
	o_List* list_add_self = list_add->self;
	if (list_add_self->length == 0) return;
	if (!basic_strcmp(self->name, list_add_self->name)) return;
	Node* tmp = list_add_self->head;
	for (size_t i = 0; i < list_add_self->length; ++i) {
		List_append(obj, tmp->data);
		tmp = tmp->next;
	}
}

private_fun boolean List_isEmpty(void* obj)
{
	if (!obj) return true;
	List* this = obj;
	o_List* self = this->self;
	if (self->length == 0) return true;
	else return false;
}

private_fun size_t List_size(void* obj)
{
	if (!obj) return 0;
	List* this = obj;
	o_List* self = this->self;
	return self->length;
}

private_fun List* List_subList(void* obj, size_t start, size_t end)
{
	if (!obj) return NULL;
	if (start < 0) return NULL;
	if (start > end) return NULL;
	List* this = obj;
	o_List* self = this->self;
	List* sub = List_ctor(self->name);
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