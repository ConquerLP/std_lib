#include "hashtable.h"
#include "hashtable.r"

#include "array.h"
#include "array.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

/* function prototypes */
/* overriding methods */
private_fun char* Hashtable_toString(void* obj);
private_fun void* Hashtable_clone(void* obj);
private_fun void Hashtable_dtor(void* obj);
private_fun boolean Hashtable_equals(void* obj, void* obj2);

/* methods */
private_fun void Hashtable_clear(void* obj);
private_fun boolean Hashtable_containsValue(void* obj, void* value);
private_fun boolean Hashtable_containsKey(void* obj, void* key);
private_fun void* Hashtable_getByKey(void* obj, void* key);
private_fun void* Hashtable_getByValue(void* obj, void* value);
private_fun void Hashtable_put(void* obj, void* key, void* value);
private_fun void Hashtable_removeByKey(void* obj, void* key);
private_fun void Hashtable_removeByValue(void* obj, void* value);
private_fun void Hashtable_removeByKeyAndValue(void* obj, void* key, void* value);
private_fun void Hashtable_replace(void* obj, void* key, void* new_value);
private_fun size_t Hashtable_getSize(void* obj);
private_fun void Hashtable_resize(void* obj, size_t new_size);
private_fun boolean Hashtable_isEmpty(void* obj);
private_fun Hashfunction_calcHash* Hashtable_getHashFunction(void* obj);
private_fun Array* Hashtable_getMappedIndices(void* obj);
private_fun size_t Hashtable_getMappedCount(void* obj);

/* helper functions */
private_fun void Hashtable_rehash(void* obj);

/* public functions */
Hashtable* Hashtable_ctor(size_t size, float factor, Hashfunction_calcHash* f, Hashfunciton_compareKey k, Hashfunciton_compareValue v)
{
	if (!f) return NULL;
	if (size <= 0) return NULL;
	if (factor < 0) return NULL;
	BASIC_CTOR(Hashtable);
	super->o_IF->clone = &Hashtable_clone;
	super->o_IF->dtor = &Hashtable_dtor;
	super->o_IF->equals = &Hashtable_equals;
	super->o_IF->toString = &Hashtable_toString;

	thisIF->clear = &Hashtable_clear;
	thisIF->containsValue = &Hashtable_containsValue;
	thisIF->containsKey = &Hashtable_containsKey;
	thisIF->getByKey = &Hashtable_getByKey;
	thisIF->getByValue = &Hashtable_getByValue;
	thisIF->put = &Hashtable_put;
	thisIF->removeByKey = &Hashtable_removeByKey;
	thisIF->removeByValue = &Hashtable_removeByValue;
	thisIF->removeByKeyAndValue = &Hashtable_removeByKeyAndValue;
	thisIF->replace = &Hashtable_replace;
	thisIF->getSize = &Hashtable_getSize;
	thisIF->getHashfunction = &Hashtable_getHashFunction;
	thisIF->getMappedIndices = &Hashtable_getMappedIndices;
	thisIF->getMappedCount = &Hashtable_getMappedCount;

	self->calcHash = f;
	self->number_of_elements = 0;
	self->factor = factor;
	self->size = size;
	o_Hashentry** entries;
	_MALLOC(o_Hashentry*, size, entries);
	for (size_t i = 0; i < size; ++i) {
		entries[i] = NULL;
	}
	return this;
}

/* Hashtable methods */

/* overriding object methods */
private_fun char* Hashtable_toString(void* obj);
private_fun void* Hashtable_clone(void* obj);
private_fun void Hashtable_dtor(void* obj);
private_fun boolean Hashtable_equals(void* obj, void* obj2);

/* Hashtable only methods */
private_fun void Hashtable_clear(void* obj);
private_fun boolean Hashtable_containsValue(void* obj, void* value);
private_fun boolean Hashtable_containsKey(void* obj, void* key);
private_fun void* Hashtable_getByKey(void* obj, void* key);
private_fun void* Hashtable_getByValue(void* obj, void* value);
private_fun void Hashtable_put(void* obj, void* key, void* value);
private_fun void Hashtable_removeByKey(void* obj, void* key);
private_fun void Hashtable_removeByValue(void* obj, void* value);
private_fun void Hashtable_removeByKeyAndValue(void* obj, void* key, void* value);
private_fun void Hashtable_replace(void* obj, void* key, void* new_value);
private_fun size_t Hashtable_getSize(void* obj);
private_fun void Hashtable_resize(void* obj, size_t new_size);
private_fun boolean Hashtable_isEmpty(void* obj);
private_fun Hashfunction_calcHash* Hashtable_getHashFunction(void* obj);
private_fun Array* Hashtable_getMappedIndices(void* obj);
private_fun size_t Hashtable_getMappedCount(void* obj);

/* helper functions */
private_fun void Hashtable_rehash(void* obj);