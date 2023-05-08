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
	char token;
	size_t count_of_lines;
}o_Filemanager;

#endif