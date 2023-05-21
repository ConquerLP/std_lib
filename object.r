#ifndef OBJECT_R

#define OBJECT_R

#include "def.h"

/* Object class */

typedef struct {
	char* name;
	void* sub;
}o_Object;

void Object_dtor(void* obj);
char* Object_getName(void* obj);

#endif