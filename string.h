#ifndef STRING_H

#define STRING_H

#include "object.h"

typedef struct {
	void (*setText)(void* obj, const char* text);
}StringIF;

typedef struct _String {
	void* super; // must be first
	void* self;	
	ObjectIF* objectIF;
	StringIF* stringIF;
}String;

/* public functions */
String* String_ctor(const char* text);

#endif // !STRING_H
