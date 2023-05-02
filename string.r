#ifndef STRING_R

#define STRING_R

#include <stdlib.h>

/* String class */

typedef struct {
	char* str;
	size_t length;
	void* sub;
}o_String;

#endif