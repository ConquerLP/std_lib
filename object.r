#ifndef OBJECT_R

#define OBJECT_R

/* Object class */

typedef struct {
	void* sub;
	char* name;
}o_Object;

void Object_dtor(void* obj);

#endif