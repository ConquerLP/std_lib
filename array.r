#ifndef ARRAY_R

#define ARRAY_R

#include <stdlib.h>

/* Array class */

typedef struct {
	void* sub;
	void** arr;
	size_t length;
	char* name;
}o_Array;

#endif