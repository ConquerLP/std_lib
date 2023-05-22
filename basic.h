#ifndef BASIC_H

#define BASIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "def.h"
#include "object.h"

#define CAST(datatype, ptr, _return, n) \
	datatype* this##n = NULL; \
	o_##datatype* self##n = NULL; \
	if(!ptr) return _return; \
	this##n = ptr; \
	if(!this##n->self) return _return; \
	if(!this##n->super) return _return; \
	Object* object_ptr##n = this##n->super; \
	if(!object_ptr##n->self) return _return; \
	o_Object* object_ptr_self##n = object_ptr##n->self; \
	if(!basic_strcmp(#datatype, object_ptr_self##n->name)) return _return; \
	self##n = this##n->self; \

#define CAST_OBJECT(ptr, _return, n) \
	Object* this##n = NULL; \
	o_Object* self##n = NULL; \
	if(!ptr) return _return; \
	this##n = ptr; \
	if(!this##n->self) return _return; \
	self##n = this##n->self; \

/* list of allowed datatypes in the array & list */
#define BASIC_DATATYPE_LENGTH 6
extern char* basic_datatype_list[BASIC_DATATYPE_LENGTH];
extern size_t basic_datatype_list_length;
boolean basic_isAllowedType(const char* cmp);
#define BASIC_LONGEST_NUM 20

/* Helper functions */
size_t basic_strlen(const char* str);
boolean basic_strcmp(const char* s1, const char* s2);
boolean basic_strcmpIgnCase(const char* s1, const char* s2);
char* basic_strcpy(const char* str);
void basic_bin_copy(void* dest, void* source, size_t bytes, size_t offset);
void basic_memset(void* dest, char c, size_t length);
void* basic_return_by_type(void* source, const char* type, size_t index);

/* Object functions */
Object* Object_ctor(const char* name);

#ifdef __cplusplus
} // extern "C"
#endif

#endif