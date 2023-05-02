#ifndef ARRAY_H

#define ARRAY_H

typedef struct _ArrayIF {
	void (*set)(void* obj, void* data, size_t index);
	void* (*get)(void* obj, size_t index);
	size_t (*length)(void* obj);
}ArrayIF;

typedef struct _Array {
	void* super; // must be first
	void* self;
	ArrayIF* arrayIF;
	ObjectIF* objectIF;
}Array;

Array* Array_ctor(const char* name, size_t length);

#endif // !ARRAY_H