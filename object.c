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
	(*this)->objectIF->dtor(obj);
}

/* protected functions */
Object* Object_ctor(void)
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
	thisIF->equals = &Object_equals;
	return this;
}

/* Object methods */

void Object_dtor(void* obj)
{
	CAST_OBJECT(obj, , );
	FREE(this->objectIF);
	FREE(this->self);
	FREE(this);
}

private_fun char* Object_toString(void* obj)
{
	CAST_OBJECT(obj, NULL, );
	return "Object";
}

private_fun void* Object_clone(void* obj)
{
	if (!obj) return NULL;
	return Object_ctor();
}

private_fun boolean Object_equals(void* obj, void* obj2)
{
	CAST_OBJECT(obj, false, );
	CAST_OBJECT(obj2, false, 1);
	if (basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, obj),
		def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, obj2))) return true;
	return false;
}
