#include "filemanager.h"
#include "filemanager.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

#include "array.h"
#include "array.r"

#define BUFFER_SIZE 1024

/* function prototypes */
/* overriding methods */
private_fun char* Filemanager_toString(void* obj);
private_fun void* Filemanager_clone(void* obj);
private_fun void Filemanager_dtor(void* obj);
private_fun boolean Filemanager_equals(void* obj, void* obj2);

/* methods */
private_fun Array* Filemanager_scanCompleteFile(void* obj);
private_fun String* Filemanager_getLineAsString(void* obj);
private_fun double Filemanager_getLineAsDouble(void* obj);
private_fun float Filemanager_getLineAsFloat(void* obj);
private_fun int Filemanager_getLineAsInt(void* obj);
private_fun size_t Filemanager_getLineAsSize_t(void* obj);
private_fun boolean Filemanager_getLineAsBoolean(void* obj);
private_fun void Filemanager_setToken(void* obj, char token);
private_fun void Filemanager_writeAsString(void* obj, void* str);
private_fun void Filemanager_writeAsDouble(void* obj, double value);
private_fun void Filemanager_writeAsFloat(void* obj, float value);
private_fun void Filemanager_writeAsInt(void* obj, int value);
private_fun void Filemanager_writeAsSize_t(void* obj, size_t value);
private_fun void Filemanager_writeAsBoolean(void* obj, boolean value);
private_fun size_t Filemanager_getLineCount(void* obj);

/* helper functions */

/* public functions */
Filemanager* Filemanager_ctor(const char* filename_path, const char* mode)
{
	if (!filename_path) return NULL;
	if (basic_strlen(filename_path) - 1 > FILENAME_MAX) return NULL;
	if (!basic_strcmp("r", mode)
		&& !basic_strcmp("w", mode)
		&& !basic_strcmp("a", mode)
		&& !basic_strcmp("r+", mode)
		&& !basic_strcmp("w+", mode)
		&& !basic_strcmp("a+", mode)) return NULL;

	Object* super = Object_ctor("Filemanager");

	Filemanager* this;
	FilemanagerIF* thisIF;
	o_Filemanager* self;
	MALLOC(Filemanager, 1, this);
	MALLOC(FilemanagerIF, 1, thisIF);
	MALLOC(o_Filemanager, 1, self);

	((o_Object*)super->self)->sub = this;
	this->super = super;
	this->self = self;
	this->filemanagerIF = thisIF;
	this->objectIF = super->objectIF;

	super->objectIF->clone = &Filemanager_toString;
	super->objectIF->toString = &Filemanager_clone;
	super->objectIF->dtor = &Filemanager_dtor;
	super->objectIF->equals = &Filemanager_equals;
	
	thisIF->scanCompleteFile = &Filemanager_scanCompleteFile;
	thisIF->getLineAsString = &Filemanager_getLineAsString;
	thisIF->getLineAsDouble = &Filemanager_getLineAsDouble;
	thisIF->getLineAsFloat = &Filemanager_getLineAsFloat;
	thisIF->getLineAsInt = &Filemanager_getLineAsInt;
	thisIF->getLineAsSize_t = &Filemanager_getLineAsSize_t;
	thisIF->getLineAsBoolean = &Filemanager_getLineAsBoolean;
	thisIF->setToken = &Filemanager_setToken;
	thisIF->writeAsString = &Filemanager_writeAsString;
	thisIF->writeAsDouble = &Filemanager_writeAsDouble;
	thisIF->writeAsFloat = &Filemanager_writeAsFloat;
	thisIF->writeAsint = &Filemanager_writeAsInt;
	thisIF->writeAsSize_t = &Filemanager_writeAsSize_t;
	thisIF->writeAsBoolean = &Filemanager_writeAsBoolean;
	thisIF->getLineCount = &Filemanager_getLineCount;

	self->sub = NULL;
	self->token = '\n';
	self->filename_path = basic_strcpy(filename_path);
	self->count_of_lines = 0;
	self->mode = basic_strcpy(mode);
	self->file_stream = fopen(filename_path, mode);
	if (!self->file_stream) {
		FREE(self->filename_path);
		FREE(self->mode);
		FREE(self);
		FREE(this->filemanagerIF);
		Object_dtor(this->super);
		FREE(this);
		return NULL;
	}
	return this;
}

/* Filemanager methods */

/* overriding object methods */
private_fun char* Filemanager_toString(void* obj)
{
	CAST(Filemanager, obj, NULL, );
	return self->filename_path;
}

private_fun void* Filemanager_clone(void* obj)
{
	CAST(Filemanager, obj, NULL, );
	return Filemanager_ctor(self->filename_path, self->mode);
}

private_fun void Filemanager_dtor(void* obj)
{
	CAST(Filemanager, obj, , );
	fclose(self->file_stream);
	FREE(self->filename_path);
	FREE(self->mode);
	FREE(self);
	Object_dtor(this->super);
	FREE(this->filemanagerIF);
	FREE(this);
}

private_fun boolean Filemanager_equals(void* obj, void* obj2)
{
	CAST(Filemanager, obj, false, );
	CAST(Filemanager, obj2, false, 1);
	if (basic_strcmp(self->filename_path, self1->filename_path)) return true;
	return false;
}

/* Filemanager only methods */
private_fun Array* Filemanager_scanCompleteFile(void* obj)
{
	CAST(Filemanager, obj, NULL, );
	Array* arr = Array_ctor("String", Filemanager_getLineCount(obj));
	if (!arr) return NULL;
	for (size_t i = 0; i < arr->arrayIF->length(arr); ++i) {
		char buffer[BUFFER_SIZE];
		fgets(buffer, BUFFER_SIZE, self->file_stream);
		String* tmp = String_ctor(buffer);
		arr->arrayIF->set(arr, tmp, i);
		delete(tmp);
	}
	return arr;
}

private_fun String* Filemanager_getLineAsString(void* obj);
private_fun double Filemanager_getLineAsDouble(void* obj);
private_fun float Filemanager_getLineAsFloat(void* obj);
private_fun int Filemanager_getLineAsInt(void* obj);
private_fun size_t Filemanager_getLineAsSize_t(void* obj);
private_fun boolean Filemanager_getLineAsBoolean(void* obj);
private_fun void Filemanager_setToken(void* obj, char token)
{
	CAST(Filemanager, obj, , );
	self->token = token;
}

private_fun void Filemanager_writeAsString(void* obj, void* str);
private_fun void Filemanager_writeAsDouble(void* obj, double value);
private_fun void Filemanager_writeAsFloat(void* obj, float value);
private_fun void Filemanager_writeAsInt(void* obj, int value);
private_fun void Filemanager_writeAsSize_t(void* obj, size_t value);
private_fun void Filemanager_writeAsBoolean(void* obj, boolean value);
private_fun size_t Filemanager_getLineCount(void* obj)
{
	CAST(Filemanager, obj, -1, );
	if (self->count_of_lines == 0) {
		char buffer[BUFFER_SIZE];
		size_t count = 0;
		while (fgets(buffer, BUFFER_SIZE, self->file_stream)) {
			count++;
		}
		self->count_of_lines = count;
	}
	return self->count_of_lines;
}

