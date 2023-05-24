#ifndef FILESMANAGER_H

#define FILESMANAGER_H

#include "object.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "object.h"
#include "array.h"
#include "string.h"
#include <stdlib.h>

typedef struct _FilemanagerIF {
	Array* (*scanCompleteFile)(void* obj);
	String* (*getLineAsString)(void* obj);
	double (*getLineAsDouble)(void* obj);
	float (*getLineAsFloat)(void* obj);
	int (*getLineAsInt)(void* obj);
	size_t (*getLineAsSize_t)(void* obj);
	boolean (*getLineAsBoolean)(void* obj);
	void (*writeAsString)(void* obj, void* str);
	void (*writeAsDouble)(void* obj, double value);
	void (*writeAsFloat)(void* obj, float value);
	void (*writeAsint)(void* obj, int value);
	void (*writeAsSize_t)(void* obj, size_t value);
	void (*writeAsBoolean)(void* obj, boolean value);
	size_t (*getLineCount)(void* obj);
	void (*setAppend)(void* obj, const char* append);
}FilemanagerIF;

typedef struct _Filemanager {
	void* super; // must be first
	void* self;
	FilemanagerIF* _FilemanagerIF;
	ObjectIF* o_IF;
}Filemanager;

/* modes: */
/*  
* "r"	opens a file for reading, it must exist
* "w"	creates an empty file for writing, if a file with the same name exist, it's contents is erased 
* "a"	appends to a file, if the file does not exist it is created
* "r+"	opends a file for reading and writing, it must exist
* "w+"	creates an empty file for reading and writing, if a file with the same name exist, it's contents is erased 
* "a+"	opens a file for reading and appending/writing
*/
Filemanager* Filemanager_ctor(const char* filename_path, const char* mode);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // FILEMANAGER_H
