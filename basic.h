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
	if(!basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), #datatype)) return _return; \
	this##n = ptr; \
	if(!this##n->self) return _return; \
	if(!this##n->super) return _return; \
	self##n = this##n->self; \
	
#define CAST_OBJECT(ptr, _return, n) \
	Object* this##n = NULL; \
	o_Object* self##n = NULL; \
	if(!ptr) return _return; \
	if(!basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), "Object")) return _return; \
	this##n = ptr; \
	if(!this##n->self) return _return; \
	self##n = this##n->self; \

#define BASIC_CTOR(datatype) \
	datatype* this; \
	datatype##IF* thisIF; \
	o_##datatype* self; \
	MALLOC(datatype, 1, this); \
	MALLOC(datatype##IF, 1, thisIF); \
	MALLOC(o_##datatype, 1, self); \
	Object* super = Object_ctor(#datatype, this); \
	this->super = super; \
	this->self = self; \
	this->_##datatype##IF = thisIF; \
	this->o_IF = super->o_IF; \

/* list of allowed datatypes in the array & list */
#define BASIC_DATATYPE_LENGTH 6
extern char* basic_datatype_list[BASIC_DATATYPE_LENGTH];
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

/*
* Memory allocation functions
*/

#define MALLOC(data_type, size, ptr) \
	(ptr) = malloc(sizeof(data_type) * (size)); \
	if(!ptr) mem_fail(); \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, true, false, #data_type, __FILE__, __LINE__, def_counter()); \

#define REALLOC(data_type, size, old_ptr) \
	data_type* ptr0 = realloc((void*)old_ptr, sizeof(data_type) * (size)); \
	if(!ptr0) mem_fail(); \
	if(ptr0 != old_ptr) def_hashtable_set(DEF_GLOBAL_HASHTABLE, old_ptr, true, true, #data_type, __FILE__, __LINE__, \
	def_counter()); \
	old_ptr = ptr0; \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr0, true, false, #data_type, __FILE__, __LINE__, \
	def_hashtable_get_count(DEF_GLOBAL_HASHTABLE, old_ptr)); \

#define FREE(ptr) \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, true, true, \
	def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), __FILE__, __LINE__, \
	def_hashtable_get_count(DEF_GLOBAL_HASHTABLE, ptr)); \
	free(ptr); ptr = NULL; \


/* Object functions */
Object* Object_ctor(const char* info, void* link);

#ifdef __cplusplus
} // extern "C"
#endif

#endif