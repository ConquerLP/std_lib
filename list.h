#ifndef LIST_H

#define LIST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include "object.h"
#include "def.h"
#include "array.h"

typedef struct {
	void* (*get)(void* obj, size_t index);
	void (*set)(void* obj, void* data, size_t index);
	void (*append)(void* obj, void* data);
	void (*clear)(void* obj);
	void (*insert)(void* obj, void* data, size_t index);
	void (*delete)(void* obj, size_t index);
	size_t (*find)(void* obj, void* toFind);
	void (*addAll)(void* obj, void* listToAdd);
	boolean (*isEmpty)(void* obj);
	size_t (*size)(void* obj);
	struct _List* (*subList)(void* obj, size_t start, size_t end);
	Array* (*toArray)(void* obj);
}ListIF;

typedef struct _List {
	void* super; // must be first
	void* self;
	ObjectIF* o_IF;
	ListIF* _ListIF;
}List;

/* public functions */
List* List_ctor(size_t datatype);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // !LIST_H
