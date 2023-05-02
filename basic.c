#include "basic.h"

size_t def_strlen(const char* str)
{
	if (!str) return 0;
	size_t result = 0;
	while (*(str + result) != '\0') {
		result++;
	}
	return result + 1;
}

boolean def_strcmp(const char* s1, const char* s2)
{
	if (!s1) return false;
	if (!s2) return false;
	if (def_strlen(s1) != def_strlen(s2)) return false;
	for (size_t i = 0; i < def_strlen(s1); ++i) {
		if (*(s1 + i) != *(s2 + i)) return false;
	}
	return true;
}

char* def_strcpy(const char* str)
{
	if (!str) return NULL;
	char* tmp;
	MALLOC(char, def_strlen(str) + 1, tmp);
	size_t i = 0;
	while (*(str + i) != '\0') {
		*(tmp + i) = *(str + i);
		i++;
	}
	*(tmp + i) = '\0';
	return tmp;
}

void def_bin_copy(void* dest, void* source, size_t bytes, size_t offset)
{
	if (!dest) return;
	if (!source) return;
	if (bytes <= 0) return;
	for (size_t i = 0; i < bytes; ++i) {
		*((char*)dest + offset + i) = *((char*)source + i);
	}
}

void def_memset(void* dest, char c, size_t length)
{
	if (!dest) return;
	if (length <= 0) return;
	for (size_t i = 0; i < length; ++i) {
		*((char*)dest + i) = c;
	}
}