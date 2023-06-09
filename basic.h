#ifndef BASIC_H

#define BASIC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "def.h"
#include "object.h"

/* Helper functions */
boolean basic_isAllowedType(size_t data_type);
char* basic_typeToString(size_t data_type);
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
	if (!ptr) def_critical_error(def_mem_fail); \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, true, false, #data_type, __FILE__, __LINE__, __func__); \

#define REALLOC(data_type, size, old_ptr) \
	data_type* ptr0 = realloc((void*)old_ptr, sizeof(data_type) * (size)); \
	if (!ptr0) def_critical_error(def_mem_fail); \
	if (ptr0 != old_ptr) def_hashtable_set(DEF_GLOBAL_HASHTABLE, old_ptr, true, true, \
	#data_type, __FILE__, __LINE__, __func__); \
	old_ptr = ptr0; \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr0, true, false, #data_type, __FILE__, __LINE__, __func__); \

#define FREE(ptr) \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, true, true, \
	def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), __FILE__, __LINE__, __func__); \
	free(ptr); ptr = NULL; \

/* HELPER MACROS FOR ALL TYPES OF CLASSES */
#define CAST(data_type, ptr, _return, n) \
	data_type* this##n = NULL; \
	o_##data_type* self##n = NULL; \
	if (!ptr) return _return; \
	if (!basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), #data_type)) return _return; \
	this##n = ptr; \
	if (!this##n->self) return _return; \
	if (!this##n->super) return _return; \
	self##n = this##n->self; \

#define CAST_OBJECT(ptr, _return, n) \
	Object* this##n = NULL; \
	o_Object* self##n = NULL; \
	if (!ptr) return _return; \
	if (!basic_strcmp(def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), "Object")) return _return; \
	this##n = ptr; \
	if (!this##n->self) return _return; \
	self##n = this##n->self; \

#define BASIC_CTOR(data_type) \
	data_type* this = NULL; \
	data_type##IF* thisIF = NULL; \
	o_##data_type* self = NULL; \
	MALLOC(data_type, 1, this); \
	_MALLOC(data_type##IF, 1, thisIF); \
	_MALLOC(o_##data_type, 1, self); \
	Object* super = Object_ctor(#data_type, this); \
	this->super = super; \
	this->self = self; \
	this->_##data_type##IF = thisIF; \
	this->o_IF = super->o_IF; \

#define BASIC_LONGEST_NUM 20

/* Object functions */
Object* Object_ctor(const char* info, void* link);

#ifdef __cplusplus
} // extern "C"
#endif

#endif