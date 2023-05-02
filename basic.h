#ifndef BASIC_H

#define BASIC_H

#include "def.h"
#include "object.h"

/* Helper functions */
size_t def_strlen(const char* str);
boolean def_strcmp(const char* s1, const char* s2);
char* def_strcpy(const char* str);
void def_bin_copy(void* dest, void* source, size_t bytes, size_t offset);
void def_memset(void* dest, char c, size_t length);

/* Object functions */
Object* Object_ctor(const char* name);

#endif