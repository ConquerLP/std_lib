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
	void (*close)(void* obj); 
	String* (*getLineAsString)(void* obj);
	double (*getLineAsDouble)(void* obj);
	float (*getLineAsFloat)(void* obj);
	int (*getLineAsInt)(void* obj);
	size_t (*getLineAsSize_t)(void* obj);
	boolean (*getLineAsBoolean)(void* obj);
	void (*setToken)(void* obj, char token);	// default is '\n'
	void (*writeAsString)(void* obj, void* str, boolean append_flag);
	void (*writeAsDouble)(void* obj, double value, boolean append_flag);
	void (*writeAsFloat)(void* obj, float value, boolean append_flag);
	void (*writeAsint)(void* obj, int value, boolean append_flag);
	void (*writeAsSize_t)(void* obj, size_t value, boolean append_flag);
	void (*writeAsBoolean)(void* obj, boolean value, boolean append_flag);
	size_t(*getLineCount)(void* obj);

}FilemanagerIF;

typedef struct _Filemanager {
	void* super; // must be first
	void* self;
	FilemanagerIF* classIF;
	ObjectIF* objectIF;
}Filemanager;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // FILESMANAGER_H
