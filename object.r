#ifndef OBJECT_R

#define OBJECT_R

#include "def.h"

/* Object class */

typedef struct {
	void* sub;
}o_Object;

void Object_dtor(void* obj);

#endif