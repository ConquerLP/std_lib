#ifndef STRING_H

#define STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "object.h"
#include "array.h"
#include "def.h"

typedef struct {
	void (*setText)(void* obj, const char* text);
	char (*charAt)(void* obj, size_t index);
	struct _String (*stringAt)(void* obj, size_t index);
	struct _String* (*substring)(void* obj, size_t start, size_t end);
	size_t(*length)(void* obj);
	void (*toLowerCase)(void* obj);
	void (*toUpperCase)(void* obj);

	boolean(*containsChar)(void* obj, char c);
	boolean(*containsCharOffset)(void* obj, char c, size_t offset);
	size_t(*findFirstChar)(void* obj, char c);
	size_t(*findLastChar)(void* obj, char c);
	size_t(*findLastCharOffset)(void* obj, char c, size_t offset);
	size_t(*findFirstCharOffset)(void* obj, char c, size_t offset);
	Array* (*findAllChar)(void* obj, char c);
	Array* (*findAllCharOffset)(void* obj, char c, size_t offset);
	void (*replaceAllChar)(void* obj, char old, char new);
	void (*replaceFirstChar)(void* obj, char old, char new);
	void (*replaceLastChar)(void* obj, char old, char new);
	void (*replaceAllCharOffset)(void* obj, char old, char new, size_t offset);
	void (*replaceFirstCharOffset)(void* obj, char old, char new, size_t offset);
	void (*replaceLastCharOffset)(void* obj, char old, char new, size_t offset);
	
	void (*removeAllChar)(void* obj, char old);
	void (*removeFirstChar)(void* obj, char old);
	void (*removeLastChar)(void* obj, char old);
	void (*removeAllCharOffset)(void* obj, char old, size_t offset);
	void (*removeFirstCharOffset)(void* obj, char old, size_t offset);
	void (*removeLastCharOffset)(void* obj, char old, size_t offset);

	boolean(*containsSubstring)(void* obj, void* str);
	boolean(*containsSubstringOffset)(void* obj, void* str, size_t offset);
	size_t(*findFirstString)(void* obj, void* str);
	size_t(*findLastString)(void* obj, void* str);
	size_t(*findLastStringOffset)(void* obj, void* str, size_t offset);
	size_t(*findFirstStringOffset)(void* obj, void* str, size_t offset);
	Array* (*findAllSubstrings)(void* obj, void* str);
	Array* (*findAllSubstringsOffset)(void* obj, void* str, size_t offset);
	Array* (*split)(void* obj, void* str);
	void (*replaceAllSubstring)(void* obj, void* sub);
	void (*replaceFirstSubstring)(void* obj, void* sub);
	void (*replaceLastSubstring)(void* obj, void* sub);
	void (*replaceAllSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*replaceFirstSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*replaceLastSubstringOffset)(void* obj, void* sub, size_t offset);
	
	void (*removeAllSubstring)(void* obj, void* sub);
	void (*removeFirstSubstring)(void* obj, void* sub);
	void (*removeLastSubstring)(void* obj, void* sub);
	void (*removeAllSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*removeFirstSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*removeLastSubstringOffset)(void* obj, void* sub, size_t offset);

	boolean(*compare)(void* str1, void* str2);
	boolean(*compareIgnCase)(void* str1, void* str2);
	boolean(*isEmpty)(void* obj);

	void (*append)(void* str1, void* str2);
	void (*trim)(void* obj);

	struct _String* (*doubleToString)(double value);
	struct _String* (*floatToString)(float value);
	struct _String* (*intToString)(int value);
	struct _String* (*size_tToString)(size_t value);

	double (*parseDouble)(void* obj);
	float (*parseFloat)(void* obj);
	int (*parseInt)(void* obj);
	size_t(*parseSize_t)(void* obj);

}StringIF;

typedef struct _String {
	void* super; // must be first
	void* self;
	ObjectIF* objectIF;
	StringIF* stringIF;
}String;

/* public functions */
String* String_ctor(const char* text);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // !STRING_H
