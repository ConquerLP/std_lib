#include "object.h"
#include "object.r"
#include "def.h"
#include "basic.h"

/* methods prototypes */
private_fun char* Object_toString(void* obj);
private_fun void* Object_clone(void* obj);

void delete(void* obj)
{
	Object** this = obj;
	(*this)->objectIF->dtor(obj);
}

/* protected functions */
Object* Object_ctor(const char* name)
{
	Object* this;
	o_Object* self;
	ObjectIF* thisIF;
	MALLOC(Object, 1, this);
	MALLOC(o_Object, 1, self);
	MALLOC(ObjectIF, 1, thisIF);
	
	self->sub = NULL;
	this->objectIF = thisIF;
	this->self = self;
	thisIF->toString = &Object_toString;
	thisIF->clone = &Object_clone;
	thisIF->dtor = &Object_dtor;
	self->name = basic_strcpy(name);
	return this;
}

/* Object methods */

void Object_dtor(void* obj)
{
	if (!obj) return;
	Object* this = obj;
	FREE(this->objectIF);
	FREE(((o_Object*)this->self)->name);
	FREE(this->self);
	FREE(this);
}

private_fun char* Object_toString(void* obj)
{
	if (!obj) return NULL;
	o_Object* this = ((Object*)obj)->self;
	return this->name;
}

private_fun void* Object_clone(void* obj)
{
	if (!obj) return NULL;
	return Object_ctor("Object");
}