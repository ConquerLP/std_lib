#ifndef BASIC_H

#define BASIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "def.h"
#include "object.h"

/* list of allowed datatypes in the array & list */
#define BASIC_DATATYPE_LENGTH 6
extern char* basic_datatype_list[BASIC_DATATYPE_LENGTH];
extern size_t basic_datatype_list_length;
boolean basic_isAllowedType(const char* cmp);

/* Helper functions */
size_t basic_strlen(const char* str);
boolean basic_strcmp(const char* s1, const char* s2);
char* basic_strcpy(const char* str);
void basic_bin_copy(void* dest, void* source, size_t bytes, size_t offset);
void basic_memset(void* dest, char c, size_t length);

/* Object functions */
Object* Object_ctor(const char* name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif