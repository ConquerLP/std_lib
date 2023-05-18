#ifndef ARRAY_H

#define ARRAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "object.h"
#include <stdlib.h>

typedef struct _ArrayIF {
	void (*set)(void* obj, void* data, size_t index);
	void (*fill)(void* obj, void* data);
	void (*resize)(void* obj, size_t new_length);
	void* (*get)(void* obj, size_t index);
	size_t(*length)(void* obj);
}ArrayIF;

typedef struct _Array {
	void* super; // must be first
	void* self;
	ArrayIF* arrayIF;
	ObjectIF* objectIF;
}Array;

Array* Array_ctor(const char* name, size_t length);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // !ARRAY_H