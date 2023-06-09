#ifndef TEMPLATE_R

#define TEMPLATE_R

#include <stdlib.h>
#include <stdarg.h>

/* Class Hashtable */
typedef struct _o_Hashentry {
	void* key;
	void* value;
	struct _o_Hashentry* next;
}o_Hashentry;

typedef struct _o_Hashtable {
	// the real class
	void* sub;
	size_t (*calcHash)(void* key, ...);
	boolean (*compareKey)(void* key, void* key2, ...);
	boolean (*compareValue)(void* value, void* value2, ...);
	o_Hashentry** entries;
	size_t size;
	size_t number_of_elements;
	float factor;
	char* data_type;
}o_Hashtable;

#endif