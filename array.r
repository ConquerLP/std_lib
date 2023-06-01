#ifndef ARRAY_R

#define ARRAY_R

#include <stdlib.h>

/* Array class */

typedef struct {
	void* sub;
	void** arr;
	size_t length;
	DEF_ALLOWED_TYPES_ARRAY_LIST type;
}o_Array;

#endif