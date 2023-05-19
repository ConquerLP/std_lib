#ifndef OBJECT_H

#define OBJECT_H

#include "def.h"

typedef struct _ObjectIF {
	char* (*toString)(void* obj);
	void* (*clone)(void* obj);
	void (*dtor)(void* obj);
	boolean (*equals)(void* obj, void* obj2);
}ObjectIF;

typedef struct _Object {
	void* self; 
	ObjectIF* objectIF;
}Object;

/* public d_tor for every possible class */
void delete(void* obj);

#endif // !OBJECT_H