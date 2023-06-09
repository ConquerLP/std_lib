#include "hashtable.h"
#include "hashtable.r"

#include "array.h"
#include "array.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

/* MACROS */
#define HASHTABLE_CREATE_VA_LIST(start_ptr) \
	va_list arg; \
	va_start(arg, start_ptr); \

#define HASHTABLE_COMPUTE_SLOT(start_ptr) \
	HASHTABLE_CREATE_VA_LIST(start_ptr); \
	size_t slot = self->calcHash(key, arg); \
	slot = slot % self->size; \
	va_end(arg);

/* function prototypes */
/* overriding methods */
private_fun char* Hashtable_toString(void* obj);
private_fun void* Hashtable_clone(void* obj);
private_fun void Hashtable_dtor(void* obj);
private_fun boolean Hashtable_equals(void* obj, void* obj2);

/* methods */
private_fun void Hashtable_clear(void* obj);
private_fun boolean Hashtable_containsValue(void* obj, void* value);
private_fun boolean Hashtable_containsKey(void* obj, void* key, ...);
private_fun void* Hashtable_getValueByKey(void* obj, void* key, ...);
private_fun void* Hashtable_getKeyByValue(void* obj, void* value);
private_fun void Hashtable_put(void* obj, void* key, void* value, ...);
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
private_fun o_Hashentry* Hashtable_Hashentry_create(void* key, void* value);

/* public functions */
Hashtable* Hashtable_ctor(
	size_t size, float factor, 
	Hashfunction_calcHash* f, 
	Hashfunciton_compareKey* k, 
	Hashfunciton_compareValue* v)
{
	if (!f) return NULL;
	if (!k) return NULL;
	if (!v) return NULL;
	//if (!data_type) return NULL;
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
	thisIF->getValueByKey = &Hashtable_getValueByKey;
	thisIF->getKeyByValue = &Hashtable_getKeyByValue;
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
	self->compareKey = k;
	self->compareValue = v;
	//self->data_type = basic_strcpy(data_type);
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

Hashtable* Hashtable_merge(void* table1, void* table2,
	float factor,
	Hashfunction_calcHash* f,
	Hashfunciton_compareKey* k,
	Hashfunciton_compareValue* v, ...)
{
	CAST(Hashtable, table1, NULL, );
	CAST(Hashtable, table2, NULL, 1);
	if (!f) return NULL;
	Hashtable* merge = Hashtable_ctor(self->size + self1->size, factor, f, k, v);
	CAST(Hashtable, merge, NULL, 2);
	HASHTABLE_CREATE_VA_LIST(v);
	Array* tmp = Hashtable_getMappedIndices(table1);
	for (size_t i = 0; i < self->size; ++i) {
		
	}

	va_end(arg);


}

/* Hashtable methods */

/* overriding object methods */
private_fun char* Hashtable_toString(void* obj)
{
	CAST(Hashtable, obj, NULL, );
	CAST_OBJECT(this->super, NULL, 1);
	_FREE(self1->toString);
	char* tmp;
	_MALLOC(char, (self->size * 100), tmp);
	char* tmp1;
	_MALLOC(char, 100, tmp1);
	for (size_t i = 0; i < self->size; ++i) {



	}
	self1->toString = tmp;
}
private_fun void* Hashtable_clone(void* obj)
{
	CAST(Hashtable, obj, NULL, );
	return Hashtable_ctor(self->size, self->factor, 
		self->calcHash, self->compareKey, 
		self->compareValue, self->data_type);
}

private_fun void Hashtable_dtor(void* obj)
{
	CAST(Hashtable, obj, , );
	_FREE(self->entries);
	_FREE(self->data_type);
	_FREE(this->_HashtableIF);
	Object_dtor(this->super);
	FREE(this);
}

private_fun boolean Hashtable_equals(void* obj, void* obj2)
{
	CAST(Hashtable, obj, false, );
	CAST(Hashtable, obj2, false, 1);
	if (self->calcHash != self1->calcHash) return false;
	if (self->compareKey != self1->compareKey) return false;
	if (self->compareValue != self1->compareValue) return false;
	if (self->number_of_elements != self1->number_of_elements) return false;
	if (basic_strcmp(self->data_type, self1->data_type)) return false;
	return true;
}

/* Hashtable only methods */
private_fun void Hashtable_clear(void* obj)
{
	CAST(Hashtable, obj, , );
	for (size_t i = 0; i < self->size; ++i) {
		self->entries[i] = NULL;
	}
}

private_fun boolean Hashtable_containsValue(void* obj, void* value)
{

}

private_fun boolean Hashtable_containsKey(void* obj, void* key, ...)
{
	CAST(Hashtable, obj, false, );
	if (!key) return false;
	boolean result = false;
	HASHTABLE_CREATE_VA_LIST(key);
	if (!Hashtable_getValueByKey(obj, key, arg)) result = false;
	else result = true;
	va_end(arg);
	return result;
}

private_fun void* Hashtable_getValueByKey(void* obj, void* key, ...)
{
	CAST(Hashtable, obj, NULL, );
	if (!key) return NULL;
	HASHTABLE_COMPUTE_SLOT(key);
	o_Hashentry* entry = self->entries[slot];
	if (!entry) return NULL;
	else return entry->value;
}

private_fun void* Hashtable_getKeyByValue(void* obj, void* value)
{
	CAST(Hashtable, obj, NULL, );
	if (!value) return NULL;
	
	for (size_t i = 0; i < self->number_of_elements; ++i) {


	}
}

private_fun void Hashtable_put(void* obj, void* key, void* value, ...)
{
	CAST(Hashtable, obj, , );
	if (!key) return;
	if (!value) return;
	HASHTABLE_COMPUTE_SLOT(value);
	o_Hashentry* entry = self->entries[slot];
	if (!entry) {
		self->entries[slot] = Hashtable_Hashentry_create(key, value);
		self->number_of_elements++;
		return;
	}
	o_Hashentry* prev = NULL;
	while (entry != NULL) {
		if (self->compareKey(entry->key, key)) {
			entry->value = value;
			return;
		}
		prev = entry;
		entry = prev->next;
	}
	prev->next = Hashtable_Hashentry_create(key, value);
	self->number_of_elements++;
}

private_fun void Hashtable_removeByKey(void* obj, void* key)
{

}

private_fun void Hashtable_removeByValue(void* obj, void* value)
{

}

private_fun void Hashtable_removeByKeyAndValue(void* obj, void* key, void* value)
{

}

private_fun void Hashtable_replace(void* obj, void* key, void* new_value)
{

}

private_fun size_t Hashtable_getSize(void* obj)
{
	CAST(Hashtable, obj, 0, );
	return self->size;
}

private_fun void Hashtable_resize(void* obj, size_t new_size)
{
	CAST(Hashtable, obj, , );
	self->size = new_size;
	Hashtable_rehash(obj);
}

private_fun boolean Hashtable_isEmpty(void* obj)
{
	CAST(Hashtable, obj, true, );
	if (self->number_of_elements == 0) return true;
	else return false;
}

private_fun Hashfunction_calcHash* Hashtable_getHashFunction(void* obj)
{
	CAST(Hashtable, obj, NULL, );
	return self->calcHash;
}

private_fun Array* Hashtable_getMappedIndices(void* obj)
{
	CAST(Hashtable, obj, NULL, );
	if (self->number_of_elements == 0) return NULL;
	Array* tmp = Array_ctor(DEF_SIZE_T, self->number_of_elements);
	o_Hashentry* entry = NULL;
	for (size_t i = 0, j = 0; i < self->number_of_elements; ++i) {
		entry = self->entries[i];
		while (entry != NULL) {
			tmp->_ArrayIF->set(tmp, &i, j);
			j++;
			entry = entry->next;
		}
	}
	return tmp;
}

private_fun size_t Hashtable_getMappedCount(void* obj) 
{
	CAST(Hashtable, obj, 0, );
	return self->number_of_elements;
}

/* helper functions */
private_fun void Hashtable_rehash(void* obj)
{

}

private_fun o_Hashentry* Hashtable_Hashentry_create(void* key, void* value)
{
	if (!key) return NULL;
	if (!value) return NULL;
	o_Hashentry* tmp;
	_MALLOC(o_Hashentry, 1, tmp);
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return tmp;
}