#include "def.h"

#include <stdlib.h>
#include <stdio.h>

void mem_fail(void)
{
	fprintf(stdout, "Memory allocation failed.\n");
	exit(1);
}

/*
* Memory allocation functions for debugging
*/

#if DEF_DEBUG

#define DEF_PADDING 20
#define DEF_MAX_DEBUG_LIST 10000000
static void* def_pointerDebugList[DEF_MAX_DEBUG_LIST];
static boolean def_flagList[DEF_MAX_DEBUG_LIST] = { false };
static size_t def_pointerDebugListCount_index = 0;
static size_t def_pointerDebugList_count = 0;

char def_line[100] = { "*-------------------------------------------------------------------------------------------------*" };

boolean def_pointerDebugList_match(void* address, size_t* index)
{
	if (!index) exit(1);
	*index = 0;
	for (size_t i = 0; i < DEF_MAX_DEBUG_LIST; i++) {
		if (def_pointerDebugList[i] == address && def_flagList[i] == true) {
			*index = i;
			return true;
		}
	}
	if (*index == 0) {
		for (size_t i = 0; i < DEF_MAX_DEBUG_LIST; i++) {
			if (def_pointerDebugList[i] == address) {
				*index = i;
			}
		}
	}
	return false;
}

void def_pointerDebugList_add(void* address)
{
	def_pointerDebugList_count++;
	def_pointerDebugList[def_pointerDebugListCount_index] = address;
	def_pointerDebugListCount_index++;
}

void def_pointerDebugList_remove(void* address)
{
	size_t index = 0;
	if (!def_pointerDebugList_match(address, &index)) def_flagList[index] = true;
	def_pointerDebugList_count--;
}

void def_pointerDebugList_print(void)
{
	fprintf(stdout, "%s\n", def_line);
	fprintf(stdout, "PointerDebugList\n");
	fprintf(stdout, "%zu of %zu possible allcated pointers were used\n", def_pointerDebugListCount_index, DEF_MAX_DEBUG_LIST);
	fprintf(stdout, "%zu of %zu were freed\n", def_pointerDebugListCount_index - def_pointerDebugList_count, def_pointerDebugListCount_index);
	fprintf(stdout, "%*s%*s\n", -DEF_PADDING - 2, "Pointer address", -DEF_PADDING, " | Freed");
	for (size_t i = 0, j = 0; i < def_pointerDebugListCount_index; i++) {
		if (def_pointerDebugList_match(def_pointerDebugList[i], &j)) {
			fprintf(stdout, "0x%0*p | yes\n", DEF_PADDING, def_pointerDebugList[i]);
		}
		else fprintf(stdout, "0x%0*p | no\n", DEF_PADDING, def_pointerDebugList[i]);
	}
	fprintf(stdout, "%s\n", def_line);
}

#endif