#include "object.h"
#include "object.r"
#include "def.h"
#include "basic.h"

/* methods prototypes */
private_fun char* Object_toString(void* obj);
private_fun void* Object_clone(void* obj);
private_fun boolean Object_equals(void* obj, void* obj2);

void delete(void* obj)
{
	if (!obj) return;
	if (!def_hashtable_is_object(DEF_GLOBAL_HASHTABLE, obj)) return;
	Object** this = obj;
	(*this)->o_IF->dtor(obj);
}

/* protected functions */
Object* Object_ctor(const char* info, void* link)
{
	if (!info) return NULL;
	if (!link) return NULL;
	Object* this;
	ObjectIF* thisIF;
	o_Object* self;
	MALLOC(Object, 1, this);
	MALLOC(ObjectIF, 1, thisIF);
	MALLOC(o_Object, 1, self);
	
	self->sub = link;
	self->toString = basic_strcpy(info);
	this->self = self;
	this->o_IF = thisIF;
	thisIF->clone = &Object_clone;
	thisIF->toString = &Object_toString;
	thisIF->equals = &Object_equals;
	thisIF->dtor = &Object_dtor;

	return this;
}

/* Object methods */

void Object_dtor(void* obj)
{
	CAST_OBJECT(obj, , );
	FREE(self->toString);
	FREE(this->o_IF);
	FREE(this->self);
	FREE(this);
}

private_fun char* Object_toString(void* obj)
{
	CAST_OBJECT(obj, NULL, );
	return self->toString;
}

private_fun void* Object_clone(void* obj)
{
	CAST_OBJECT(obj, NULL, );
	return Object_ctor(self->toString, self->sub);
}

private_fun boolean Object_equals(void* obj, void* obj2)
{
	CAST_OBJECT(obj, false, );
	CAST_OBJECT(obj2, false, 1);
	if (basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, obj),
		def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, obj2))) return true;
	return false;
}
