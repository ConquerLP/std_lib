#ifndef DEF_H
#define DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

#define boolean char
#define true 1
#define false 0
#define global_var static
#define private_fun static
#define perm_var static
#define ARRAY_SIZE(ptr) (sizeof((ptr)) / sizeof((*ptr)))

#define DEF_HASH_TABLE_SIZE 10000
#define DEF_DEBUG_MODE true

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mem_fail(void);

/* allowed types for list and array */
enum {
	DEF_BOOLEAN = 0,
	DEF_USHORT,
	DEF_SHORT,
	DEF_CHAR,
	DEF_DEF_UINT,
	DEF_INT,
	DEF_ULONGINT,
	DEF_LONGINT,
	DEF_LONGLONGINT,
	DEF_SIZE_T,
	DEF_FLOAT,
	DEF_DOUBLE,
	DEF_LONGDOUBLE,
	DEF_STRING,
	DEF_LAST_DATATYPE
};

extern size_t DEF_DATATYPES[DEF_LAST_DATATYPE];

/* hashtable for memory allocation logging */
typedef struct _Def_Hashentry {
	void* key;
	boolean is_object;
	boolean freed;
	char* type;
	char* file;
	size_t line;
	size_t count;
	struct _Def_Hashentry* next;
}Def_Hashentry;

typedef struct _Def_Hashtable {
	Def_Hashentry** entries;
}Def_Hashtable;

size_t def_counter(void);
size_t def_hash_ptr(void* ptr);
Def_Hashtable* def_hashtable_create(void);
Def_Hashentry* def_hashentry_create(void* key, boolean is_obj, boolean freed,
	const char* type, char* file, size_t line, size_t count);
void def_hashtable_set(Def_Hashtable* table, void* key, boolean is_obj, boolean freed,
	const char* type, char* file, size_t line, size_t count);
boolean def_hashtable_is_object(Def_Hashtable* table, void* key);
void def_hashtable_print(Def_Hashtable* table);
void def_hashtable_delete(Def_Hashtable* table);
char* def_hashtable_get_type(Def_Hashtable* table, void* key);
size_t def_hashtable_get_count(Def_Hashtable* table, void* key);

#define DEF_GLOBAL_HASHTABLE def_global_hashtable
extern Def_Hashtable* DEF_GLOBAL_HASHTABLE;
#define DEF_START_UP DEF_GLOBAL_HASHTABLE = def_hashtable_create();
#define DEF_CLEAR_MEM def_hashtable_delete(DEF_GLOBAL_HASHTABLE);

#if DEF_DEBUG_MODE
	#define _PRINT_DEBUG_MEMORY def_hashtable_print(DEF_GLOBAL_HASHTABLE);
#else 
	#define _PRINT_DEBUG_MEMORY //_PRINT_DEBUG_MEMORY
#endif

/*
* Memory allocation functions
*/

#define _MALLOC(data_type, size, ptr) \
	(ptr) = malloc(sizeof(data_type) * (size)); \
	if(!ptr) mem_fail(); \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, false, false, #data_type, __FILE__, __LINE__, def_counter()); \

#define _REALLOC(data_type, size, old_ptr) \
	data_type* ptr0 = realloc((void*)old_ptr, sizeof(data_type) * (size)); \
	if(!ptr0) mem_fail(); \
	if(ptr0 != old_ptr) def_hashtable_set(DEF_GLOBAL_HASHTABLE, old_ptr, false, true, #data_type, __FILE__, __LINE__, \
	def_counter()); \
	old_ptr = ptr0; \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr0, false, false, #data_type, __FILE__, __LINE__, \
	def_hashtable_get_count(DEF_GLOBAL_HASHTABLE, old_ptr)); \

#define _FREE(ptr) \
	def_hashtable_set(DEF_GLOBAL_HASHTABLE, ptr, false, true, \
						def_hashtable_get_type(DEF_GLOBAL_HASHTABLE, ptr), __FILE__, __LINE__, \
						def_hashtable_get_count(DEF_GLOBAL_HASHTABLE, ptr)); \
	free(ptr); ptr = NULL; \

#endif

#ifdef __cplusplus
} // extern "C"
#endif
