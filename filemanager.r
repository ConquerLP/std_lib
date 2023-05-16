#ifndef FILESMANAGER_R

#define FILESMANAGER_R

#include <stdlib.h>
#include <stdio.h>

/* Filemanager class */

typedef struct _o_Filemanager{
	void* sub;
	FILE* file_stream;
	char* filename_path;
	char* mode;
	size_t count_of_lines;
	size_t current_line;
}o_Filemanager;

#endif