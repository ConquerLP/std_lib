#ifndef DEF_H
#define DEF_H

#define boolean unsigned short
#define true 1
#define false 0
#define global_var static
#define private_fun static
#define perm_var static

#define DEF_DEBUG false

#define PRINT_DEBUG_MEMORY ;

#include <stdlib.h>
#include <stdio.h>

void mem_fail(void);

/*
* Memory allocation functions
*/

#define MALLOC(data_type, size, ptr) (ptr) = malloc(sizeof(data_type) * (size)); \
if(!ptr) mem_fail(); \

#define REALLOC(data_type, size, old_ptr) data_type* ptr0 = realloc((void*)old_ptr, sizeof(data_type) * (size)); \
if(!ptr0) mem_fail(); \
else old_ptr = ptr0; \

#define FREE(ptr) free(ptr); ptr = NULL;

#endif

/*
* Memory allocation functions for debugging
*/

#if DEF_DEBUG

#define MALLOC DEBUG_MALLOC
#define REALLOC DEBUG_REALLOC
#define FREE DEBUG_FREE

extern char def_line[100];
boolean def_pointerDebugList_match(void* address, size_t* index);
void def_pointerDebugList_add(void* address);
void def_pointerDebugList_remove(void* address);
void def_pointerDebugList_print(void);

#define DEBUG_MALLOC(data_type, size, ptr) (ptr) = malloc(sizeof(data_type) * (size)); \
if(!ptr) mem_fail(); \
def_pointerDebugList_add((void*)ptr); \
fprintf(stdout, "%s\n", def_line); \
fprintf(stdout, "Called malloc. Datatype was: '%s' Size was: '%zu'\nIn File: %s\nAt Line: '%d'\n", #data_type, size, __FILE__, __LINE__); \
fprintf(stdout, "Allocated pointer adress was: 0x%p\n", ptr); \
fprintf(stdout, "%s\n", def_line); \

#define DEBUG_REALLOC(data_type, size, old_ptr) fprintf(stdout, "%s\n", def_line); \
fprintf(stdout, "Old pointer address was: 0x%p\n", old_ptr); \
data_type* ptr0 = realloc((void*)old_ptr, sizeof(data_type) * (size)); \
if(!ptr0) mem_fail(); \
if(ptr0 != old_ptr) {def_pointerDebugList_add((void*)ptr0); def_pointerDebugList_remove((void*)old_ptr); old_ptr = NULL;}\
old_ptr = ptr0; \
fprintf(stdout, "Called realloc. Datatype was: '%s' Size was: '%zu'\nIn File: %s\nAt Line: '%d'\n", #data_type, size, __FILE__, __LINE__); \
fprintf(stdout, "New allocated pointer address was: 0x%p\n", ptr0); \
fprintf(stdout, "%s\n", def_line); \

#define DEBUG_FREE(ptr) fprintf(stdout, "%s\n", def_line); \
fprintf(stdout, "Called free.\nIn File: %s\nAt Line: '%d'\n", __FILE__, __LINE__); \
fprintf(stdout, "Freed pointer was: 0x%p\n", ptr); \
def_pointerDebugList_remove((void*)ptr); \
free(ptr); ptr = NULL; \
fprintf(stdout, "%s\n", def_line); \

#define PRINT_DEBUG_MEMORY def_pointerDebugList_print();

#endif
