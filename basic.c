#include "basic.h"
#include "def.h"

size_t DEF_DATATYPES[DEF_LAST_DATATYPE] = {
	DEF_BOOLEAN,
	DEF_CHAR,
	DEF_USHORT,
	DEF_SHORT,
	DEF_UINT,
	DEF_INT,
	DEF_ULONGINT,
	DEF_LONGINT,
	DEF_LONGLONGINT,
	DEF_SIZE_T,
	DEF_FLOAT,
	DEF_DOUBLE,
	DEF_LONGDOUBLE,
	DEF_STRING,
};

boolean basic_isAllowedType(size_t data_type)
{
	if (data_type < 0) return false;
	if (data_type >= DEF_LAST_DATATYPE) return false;
	else return true;
}

char* basic_typeToString(size_t data_type)
{
	if (!basic_isAllowedType(data_type)) return NULL;
	switch (data_type) {
	case DEF_BOOLEAN:		return "boolean"; 
	case DEF_USHORT:		return "unsigned short"; 
	case DEF_SHORT:			return "short"; 
	case DEF_CHAR:			return "char"; 
	case DEF_UINT:		return "unsigned int"; 
	case DEF_INT:			return "int"; 
	case DEF_ULONGINT:		return "unsigned int"; 
	case DEF_LONGINT:		return "long int"; 
	case DEF_LONGLONGINT:	return "long long int"; 
	case DEF_SIZE_T:		return "size_t"; 
	case DEF_FLOAT:			return "float"; 
	case DEF_DOUBLE:		return "double"; 
	case DEF_LONGDOUBLE:	return "longe double"; 
	case DEF_STRING:		return "String"; 
	default:				return NULL;
	}
}

size_t basic_strlen(const char* str)
{
	if (!str) return 0;
	size_t result = 0;
	while (*(str + result) != '\0') {
		result++;
	}
	return result + 1;
}

boolean basic_strcmp(const char* s1, const char* s2)
{
	if (!s1) return false;
	if (!s2) return false;
	if (basic_strlen(s1) != basic_strlen(s2)) return false;
	for (size_t i = 0; i < basic_strlen(s1); ++i) {
		if (*(s1 + i) != *(s2 + i)) return false;
	}
	return true;
}

boolean basic_strcmpIgnCase(const char* s1, const char* s2)
{
	if (!s1) return false;
	if (!s2) return false;
	if (basic_strlen(s1) != basic_strlen(s2)) return false;
	char a = *s1, b = *s2;
	for (size_t i = 0; i < basic_strlen(s1) - 1; ++i) {
		if (*(s1 + i) >= 97 && *(s1 + i) < 123) {
			a = *(s1 + i) - 32;
		}
		else a = *(s1 + i);
		if (*(s2 + i) >= 97 && *(s2 + i) < 123) {
			b = *(s2 + i) - 32;
		}
		else b = *(s2 + i);
		if (a != b) return false;
	}
	return true;
}

char* basic_strcpy(const char* str)
{
	if (!str) return NULL;
	char* tmp;
	_MALLOC(char, basic_strlen(str) + 1, tmp);
	size_t i = 0;
	while (*(str + i) != '\0') {
		*(tmp + i) = *(str + i);
		i++;
	}
	*(tmp + i) = '\0';
	return tmp;
}

void basic_bin_copy(void* dest, void* source, size_t bytes, size_t offset)
{
	if (!dest) return;
	if (!source) return;
	if (bytes <= 0) return;
	for (size_t i = 0; i < bytes; ++i) {
		*((char*)dest + offset + i) = *((char*)source + i);
	}
}

void basic_memset(void* dest, char c, size_t length)
{
	if (!dest) return;
	if (length <= 0) return;
	for (size_t i = 0; i < length; ++i) {
		*((char*)dest + i) = c;
	}
}

void* basic_return_by_type(void* source, const char* type, size_t index)
{
	if (!source) return NULL;
	if (!type) return NULL;
	if (basic_strcmp(type, "double")) {
		return (double*)source + index;
	}
	if (basic_strcmp(type, "float")) {
		return (float*)source + index;
	}
	if (basic_strcmp(type, "int")) {
		return (int*)source + index;
	}
	if (basic_strcmp(type, "size_t")) {
		return (size_t*)source + index;
	}
	return NULL;
}
