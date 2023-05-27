#ifndef HASHTABLE_H

#define HASHTABLE_H

#include "object.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "object.h"
#include "array.h"
#include <stdlib.h>

typedef size_t (Hashfunction_calcHash) (void* key, ...);
typedef boolean (Hashfunciton_compareKey) (void* key, void* key2, ...);
typedef boolean (Hashfunciton_compareValue) (void* value, void* value2, ...);

typedef struct _HashtableIF {
	void (*clear)(void* obj);
	boolean(*containsValue)(void* obj, void* value);
	boolean(*containsKey)(void* obj, void* key);
	void* (*getByKey)(void* obj, void* key);
	void* (*getByValue)(void* obj, void* value);
	void (*put)(void* obj, void* key, void* value);
	void (*removeByKey)(void* obj, void* key);
	void (*removeByValue)(void* obj, void* value);
	void (*removeByKeyAndValue)(void* obj, void* key, void* value);
	void (*replace)(void* obj, void* key, void* new_value);
	size_t (*getSize)(void* obj);
	void (*resize)(void* obj, size_t new_size);
	boolean(*isEmpty)(void* obj);
	Hashfunction_calcHash* (*getHashfunction)(void* obj);
	Array* (*getMappedIndices)(void* obj);
	size_t(*getMappedCount)(void* obj);
}HashtableIF;

typedef struct _Hashtable {
	void* super; // must be first
	void* self;
	HashtableIF* _HashtableIF;
	ObjectIF* o_IF;
}Hashtable;

Hashtable* Hashtable_ctor(size_t size, float factor, Hashfunction_calcHash* f, Hashfunciton_compareKey k, Hashfunciton_compareValue v);
Hashtable* Hashtable_merge(void* table1, void* table2, Hashfunction_calcHash* f);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // HASHTABLE_H
