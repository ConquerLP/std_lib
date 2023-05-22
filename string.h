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
	size_t(*length)(void* obj);
	void (*toLowerCase)(void* obj);
	void (*toUpperCase)(void* obj);

	boolean(*startsWithChar)(void* obj, char c);
	boolean(*endsWithChar)(void* obj, char c);
	boolean(*containsChar)(void* obj, char c);
	boolean(*containsCharOffset)(void* obj, char c, size_t offset);
	size_t(*countOccurencesChar)(void* obj, char c);
	size_t(*countOccurencesCharOffset)(void* obj, char c, size_t offset);
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
	void (*insertCharAt)(void* obj, char c, size_t index);

	boolean(*startsWithString)(void* obj, void* str);
	boolean(*endsWithString)(void* obj, void* str);
	boolean(*containsSubstring)(void* obj, void* str);
	boolean(*containsSubstringOffset)(void* obj, void* str, size_t offset);
	size_t(*countSubstringOccurences)(void* obj, void* str);
	size_t(*countSubstringOccurencesOffset)(void* obj, void* str, size_t offset);
	size_t(*findFirstString)(void* obj, void* str);
	size_t(*findLastString)(void* obj, void* str);
	size_t(*findLastStringOffset)(void* obj, void* str, size_t offset);
	size_t(*findFirstStringOffset)(void* obj, void* str, size_t offset);
	Array* (*findAllSubstrings)(void* obj, void* str);
	Array* (*findAllSubstringsOffset)(void* obj, void* str, size_t offset);
	Array* (*split)(void* obj, void* str);
	void (*replaceAllSubstring)(void* obj, void* sub, void* replacement);
	void (*replaceFirstSubstring)(void* obj, void* sub, void* replacement);
	void (*replaceLastSubstring)(void* obj, void* sub, void* replacement);
	void (*replaceAllSubstringOffset)(void* obj, void* replacement, void* sub, size_t offset);
	void (*replaceFirstSubstringOffset)(void* obj, void* replacement, void* sub, size_t offset);
	void (*replaceLastSubstringOffset)(void* obj, void* replacement, void* sub, size_t offset);
	
	void (*removeAllSubstring)(void* obj, void* sub);
	void (*removeFirstSubstring)(void* obj, void* sub);
	void (*removeLastSubstring)(void* obj, void* sub);
	void (*removeAllSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*removeFirstSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*removeLastSubstringOffset)(void* obj, void* sub, size_t offset);
	void (*insertStringAt)(void* obj, void* str, size_t index);

	boolean(*compare)(void* str1, void* str2);
	boolean(*compareIgnCase)(void* str1, void* str2);
	boolean(*isEmpty)(void* obj);

	void (*append)(void* str1, void* str2);
	void (*trim)(void* obj, const char* toTrim);

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
/* main ctor */
String* String_ctor(const char* text);

/* alternative ctors */
String* String_doubleToString(double value, int prec);
String* String_floatToString(float value, int prec);
String* String_intToString(int value);
String* String_size_tToString(size_t value);
String* String_booleanToString(boolean value);
String* String_stringAt(void* obj, size_t index);
String* String_subString(void* obj, size_t start, size_t end);
String* String_join(void* obj);

#define _setS(string, new_str) string->stringIF->setText(string, new_str);
#define _printS(string) string->objectIF->toString(string)
#define _containsS(string, sub) string->stringIF->containsSubstring(string, String_ctor(sub))
#define _compareS(string, cmp) string->stringIF->compare(string, String_ctor(cmp))
#define _compareIgnCaseS(string, cmp) string->stringIF->compareIgnCase(string, String_ctor(cmp))

#ifdef __cplusplus
} // extern "C"
#endif

#endif // !STRING_H
