#include "filemanager.h"
#include "filemanager.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

#include "array.h"
#include "array.r"

#include "string.h"
#include "string.r"

#define BUFFER_SIZE 1024
#define RESET_FILE \
	fclose(self->file_stream); \
	self->file_stream = fopen(self->filename_path, self->mode); \
	if (!self->file_stream) exit(1); \

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
private_fun void Filemanager_writeAsString(void* obj, void* str);
private_fun void Filemanager_writeAsDouble(void* obj, double value);
private_fun void Filemanager_writeAsFloat(void* obj, float value);
private_fun void Filemanager_writeAsInt(void* obj, int value);
private_fun void Filemanager_writeAsSize_t(void* obj, size_t value);
private_fun void Filemanager_writeAsBoolean(void* obj, boolean value);
private_fun size_t Filemanager_getLineCount(void* obj);
private_fun void Filemanager_setAppend(void* obj, const char* append);

/* helper functions */
boolean Filemanager_allowed_modes(const char* cmp);

/* public functions */
Filemanager* Filemanager_ctor(const char* filename_path, const char* mode)
{
	if (!filename_path) return NULL;
	if (basic_strlen(filename_path) - 1 > FILENAME_MAX) return NULL;
	if (!Filemanager_allowed_modes(mode)) return NULL;

	BASIC_CTOR(Filemanager);

	super->o_IF->clone = &Filemanager_clone;
	super->o_IF->toString = &Filemanager_toString;
	super->o_IF->dtor = &Filemanager_dtor;
	super->o_IF->equals = &Filemanager_equals;
	
	thisIF->scanCompleteFile = &Filemanager_scanCompleteFile;
	thisIF->getLineAsString = &Filemanager_getLineAsString;
	thisIF->getLineAsDouble = &Filemanager_getLineAsDouble;
	thisIF->getLineAsFloat = &Filemanager_getLineAsFloat;
	thisIF->getLineAsInt = &Filemanager_getLineAsInt;
	thisIF->getLineAsSize_t = &Filemanager_getLineAsSize_t;
	thisIF->getLineAsBoolean = &Filemanager_getLineAsBoolean;
	thisIF->writeAsString = &Filemanager_writeAsString;
	thisIF->writeAsDouble = &Filemanager_writeAsDouble;
	thisIF->writeAsFloat = &Filemanager_writeAsFloat;
	thisIF->writeAsint = &Filemanager_writeAsInt;
	thisIF->writeAsSize_t = &Filemanager_writeAsSize_t;
	thisIF->writeAsBoolean = &Filemanager_writeAsBoolean;
	thisIF->getLineCount = &Filemanager_getLineCount;
	thisIF->setAppend = &Filemanager_setAppend;

	self->sub = NULL;
	self->filename_path = basic_strcpy(filename_path);
	self->count_of_lines = 0;
	self->current_line = 0;
	self->std_append = basic_strcpy("\n");
	self->mode = basic_strcpy(mode);
	self->file_stream = fopen(filename_path, mode);
	if (!self->file_stream) exit(1);
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, self->file_stream) != NULL) {
		self->count_of_lines++;
	}
	RESET_FILE;
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
	_FREE(self->filename_path);
	_FREE(self->std_append);
	_FREE(self->mode);
	_FREE(self);
	Object_dtor(this->super);
	_FREE(this->_FilemanagerIF);
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
	Array* arr = Array_ctor(DEF_STRING, Filemanager_getLineCount(obj));
	if (!arr) return NULL;
	char buffer[BUFFER_SIZE] = {0};
	for (size_t i = 0; i < arr->_ArrayIF->length(arr); ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
		String* tmp = String_ctor(buffer);
		arr->_ArrayIF->set(arr, tmp, i);
		delete(tmp);
	}
	RESET_FILE;
	return arr;
}

private_fun String* Filemanager_getLineAsString(void* obj)
{
	CAST(Filemanager, obj, NULL, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return NULL;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	RESET_FILE;
	return String_ctor(buffer);
}

private_fun double Filemanager_getLineAsDouble(void* obj)
{
	CAST(Filemanager, obj, 0.0, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return 0.0;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	String* tmp = String_ctor(buffer);
	double result = tmp->_StringIF->parseDouble(tmp);
	delete(tmp);
	RESET_FILE;
	return result;
}

private_fun float Filemanager_getLineAsFloat(void* obj)
{
	CAST(Filemanager, obj, 0.0, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return 0.0;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	String* tmp = String_ctor(buffer);
	float result = tmp->_StringIF->parseFloat(tmp);
	delete(tmp);
	RESET_FILE;
	return result;
}

private_fun int Filemanager_getLineAsInt(void* obj)
{
	CAST(Filemanager, obj, 0, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return 0;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	String* tmp = String_ctor(buffer);
	int result = tmp->_StringIF->parseInt(tmp);
	delete(tmp);
	RESET_FILE;
	return result;
}

private_fun size_t Filemanager_getLineAsSize_t(void* obj)
{
	CAST(Filemanager, obj, 0, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return 0;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	String* tmp = String_ctor(buffer);
	size_t result = tmp->_StringIF->parseSize_t(tmp);
	delete(tmp);
	RESET_FILE;
	return result;
}

private_fun boolean Filemanager_getLineAsBoolean(void* obj)
{
	CAST(Filemanager, obj, 0, );
	char buffer[BUFFER_SIZE];
	self->current_line++;
	if (self->current_line > self->count_of_lines) return 0;
	for (size_t i = 0; i < self->current_line; ++i) {
		fgets(buffer, BUFFER_SIZE, self->file_stream);
	}
	String* tmp = String_ctor(buffer);
	boolean result = tmp->_StringIF->parseInt(tmp);
	delete(tmp);
	RESET_FILE;
	if (result >= 1) return true;
	if (result <= 0) return false;
	return false;
}

private_fun void Filemanager_writeAsString(void* obj, void* str)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	if (!def_hashtable_is_object(DEF_GLOBAL_HASHTABLE, str)) {
		String* tmp = String_ctor(str);
		Filemanager_writeAsString(obj, tmp);
		delete(tmp);
		return;
	}
	CAST(String, str, , 1);
	fflush(self->file_stream);
	fprintf(self->file_stream, "%s%s", self1->str, self->std_append);
}

private_fun void Filemanager_writeAsDouble(void* obj, double value)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	fflush(self->file_stream);
	fprintf(self->file_stream, "%lf%s", value, self->std_append);
}

private_fun void Filemanager_writeAsFloat(void* obj, float value)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	fflush(self->file_stream);
	fprintf(self->file_stream, "%f%s", value, self->std_append);
}

private_fun void Filemanager_writeAsInt(void* obj, int value)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	fflush(self->file_stream);
	fprintf(self->file_stream, "%i%s", value, self->std_append);
}

private_fun void Filemanager_writeAsSize_t(void* obj, size_t value)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	fflush(self->file_stream);
	fprintf(self->file_stream, "%zu%s", value, self->std_append);
}

private_fun void Filemanager_writeAsBoolean(void* obj, boolean value)
{
	CAST(Filemanager, obj, , );
	//file is only for reading
	if (basic_strcmp(self->mode, "r")) return;
	fflush(self->file_stream);
	fprintf(self->file_stream, "%i%s", value, self->std_append);
}

private_fun size_t Filemanager_getLineCount(void* obj)
{
	CAST(Filemanager, obj, -1, );
	return self->count_of_lines;
}

private_fun void Filemanager_setAppend(void* obj, const char* append)
{
	CAST(Filemanager, obj, , );
	_FREE(self->std_append);
	self->std_append = basic_strcpy(append);
}

/* helper functions */
boolean Filemanager_allowed_modes(const char* mode)
{
	if (!mode) return false;
	char* allowed_mode[] = {
		"r",
		"w",
		"a",
		"r+",
		"w+",
		"a+"
	};
	for (size_t i = 0; i < ARRAY_SIZE(allowed_mode); ++i) {
		if (basic_strcmp(allowed_mode[i], mode)) return true;
	}
	return false;
}