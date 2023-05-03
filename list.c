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

	//function links
	//listIF->...

	this->objectIF = super->objectIF;
	this->super = super;

	//super functions links

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
private_fun char* List_toString(void* obj);
private_fun void List_dtor(void* obj);
private_fun void* List_clone(void* obj);

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
	}
	self->length++;
	List_set(obj, data, self->length);
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
	if (node == self->head) {
		if (node->next) {
			node->next->prev = NULL;
			self->head = node->next;
			node->next = NULL;
			node->prev = NULL;
		}
	}
	else if (node == self->tail) {
		node->prev->next = NULL;
		self->tail = node->prev;
		node->next = NULL;
		node->prev = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = NULL;
		node->prev = NULL;
	}
	FREE(node);
	self->length--;
}

private_fun size_t List_find(void* obj, void* toFind)
{
	
}

private_fun void List_addAll(void* obj, void* listToAdd);

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

private_fun List* List_subList(void* obj, size_t start, size_t end);

/* helper functions */
private_fun Node* List_getNode(List* this, size_t index)
{
	if (!this) return NULL;
	if (index < 0) return NULL;
	o_List* self = this->self;
	if (self->length == 0) return NULL;
	if (index == 0) self->head;
	if (index >= self->length) return self->tail;
	Node* tmp = self->head;
	for (size_t i = 0; i < self->length; ++i) {
		tmp = tmp->next;
	}
	return tmp;
}