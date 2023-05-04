#include "string.h"
#include "string.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

/* function prototypes */
/* Helper functions*/
private_fun boolean String_cmpChar(char a, char b, boolean ignCase);
private_fun char String_CharToLower(char a);

/* overriding methods */
private_fun char* String_toString(void* obj);
private_fun void* String_clone(void* obj);
private_fun void String_dtor(void* obj);
private_fun boolean String_equals(void* obj, void* obj2);

/* methods */
private_fun void String_setText(void* obj, const char* text);
private_fun char String_charAt(void* obj, size_t index);
private_fun String* String_stringAt(void* obj, size_t index);
private_fun String* String_subString(void* obj, size_t start, size_t end);
private_fun size_t String_length(void* obj);
private_fun void String_toLowerCase(void* obj);
private_fun void String_toUpperCase(void* obj);

private_fun boolean String_containsChar(void* obj, char c);
private_fun boolean String_containsCharOffset(void* obj, char c, size_t offset);
private_fun size_t String_findFirstChar(void* obj, char c);
private_fun size_t String_findLastChar(void* obj, char c);
private_fun size_t String_findLastCharOffset(void* obj, char c, size_t offset);
private_fun size_t String_findFirstCharOffset(void* obj, char c, size_t offset);

private_fun void String_replaceAllChar(void* obj, char old, char new);
private_fun void String_replaceFirstChar(void* obj, char old, char new);
private_fun void String_replaceLastChar(void* obj, char old, char new);
private_fun void String_replaceAllCharOffset(void* obj, char old, char new, size_t offset);
private_fun void String_replaceFirstCharOffset(void* obj, char old, char new, size_t offset);
private_fun void String_replaceLastCharOffset(void* obj, char old, char new, size_t offset);

private_fun boolean String_containsSubstring(void* obj, void* str);
private_fun boolean String_containsSubstringOffset(void* obj, void* str, size_t offset);
private_fun size_t String_findFirstString(void* obj, void* str);
private_fun size_t String_findLastString(void* obj, void* str);
private_fun size_t String_findLastStringOffset(void* obj, void* str, size_t offset);
private_fun size_t String_findFirstStringOffset(void* obj, void* str, size_t offset);
private_fun Array* String_findAllSubstrings(void* obj, void* str);
private_fun Array* String_findAllSubstringsOffset(void* obj, void* str, size_t offset);
private_fun Array* String_split(void* obj, void* str);
private_fun void String_replaceAllSubstring(void* obj, void* sub);
private_fun void String_replaceFirstSubstring(void* obj, void* sub);
private_fun void String_replaceLastSubstring(void* obj, void* sub);
private_fun void String_replaceAllSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_replaceFirstSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_replaceLastSubstringOffset(void* obj, void* sub, size_t offset);

private_fun boolean String_compare(void* obj, void* str2);
private_fun boolean String_compareIgnCase(void* obj, void* str2);
private_fun boolean Stringis_Empty(void* obj);

private_fun void String_append(void* str1, void* str2);
private_fun void String_trim(void* obj);

private_fun String* String_doubleToString(double value);
private_fun String* String_floatToString(float value);
private_fun String* String_intToString(int value);
private_fun String* String_size_tToString(size_t value);

private_fun double String_parseDouble(void* obj);
private_fun float String_parseFloat(void* obj);
private_fun int String_parseInt(void* obj);
private_fun size_t String_parseSize_t(void* obj);

/* public functions */
String* String_ctor(const char* text)
{
	if (!text) return NULL;
	Object* super = Object_ctor("String");

	String* this;
	StringIF* thisIF;
	o_String* self;
	MALLOC(String, 1, this);
	MALLOC(StringIF, 1, thisIF);
	MALLOC(o_String, 1, self);

	this->self = self;
	this->stringIF = thisIF;
	this->objectIF = super->objectIF;

	super->objectIF->toString = &String_toString;
	super->objectIF->clone = &String_clone;
	super->objectIF->dtor = &String_dtor;
	super->objectIF->equals = &String_equals;

	thisIF->setText = &String_setText;

	thisIF->setText = &String_charAt;
	thisIF->setText = &String_stringAt;
	thisIF->setText = &String_subString;
	thisIF->setText = &String_length;
	thisIF->setText = &String_toLowerCase;
	thisIF->setText = &String_toUpperCase;

	thisIF->setText = &String_containsChar;
	thisIF->setText = &String_containsCharOffset;
	thisIF->setText = &String_findFirstChar;
	thisIF->setText = &String_findLastChar;
	thisIF->setText = &String_findLastCharOffset;
	thisIF->setText = &String_findFirstCharOffset;

	thisIF->setText = &String_replaceAllChar;
	thisIF->setText = &String_replaceFirstChar;
	thisIF->setText = &String_replaceLastChar;
	thisIF->setText = &String_replaceAllCharOffset;
	thisIF->setText = &String_replaceFirstCharOffset;
	thisIF->setText = &String_replaceLastCharOffset;

	thisIF->setText = &String_containsSubstring;
	thisIF->setText = &String_containsSubstringOffset;
	thisIF->setText = &String_findFirstString;
	thisIF->setText = &String_findLastString;
	thisIF->setText = &String_findLastStringOffset;
	thisIF->setText = &String_findFirstStringOffset;
	thisIF->setText = &String_findAllSubstrings;
	thisIF->setText = &String_findAllSubstringsOffset;
	thisIF->setText = &String_split;
	thisIF->setText = &String_replaceAllSubstring;
	thisIF->setText = &String_replaceFirstSubstring;
	thisIF->setText = &String_replaceLastSubstring;
	thisIF->setText = &String_replaceAllSubstringOffset;
	thisIF->setText = &String_replaceFirstSubstringOffset;
	thisIF->setText = &String_replaceLastSubstringOffset;

	thisIF->setText = &String_compare;
	thisIF->setText = &String_compareIgnCase;
	thisIF->setText = &Stringis_Empty;

	thisIF->setText = &String_append;
	thisIF->setText = &String_trim;

	thisIF->setText = &String_doubleToString;
	thisIF->setText = &String_floatToString;
	thisIF->setText = &String_intToString;
	thisIF->setText = &String_size_tToString;

	thisIF->setText = &String_parseDouble;
	thisIF->setText = &String_parseFloat;
	thisIF->setText = &String_parseInt;
	thisIF->setText = &String_parseSize_t;


	this->super = super;
	self->sub = NULL;
	self->length = basic_strlen(text);
	self->str = basic_strcpy(text);

	return this;
}

/* String methods */

/* overriding object methods */
private_fun void String_dtor(void* obj)
{
	CAST(String, obj, , );

	FREE(this->stringIF);
	FREE(self->str);

	Object_dtor(this->super);
	FREE(self);
	FREE(this);
}

private_fun char* String_toString(void* obj)
{
	CAST(String, obj, NULL, );
	return self->str;
}

private_fun void* String_clone(void* obj)
{
	CAST(String, obj, NULL, );
	String* new = String_ctor(self->str);
	return new;
}

private_fun boolean String_equals(void* obj, void* obj2)
{
	CAST(String, obj, false, );
	CAST(String, obj2, false, 1);
	if (basic_strcmp(self->str, self1->str)) return true;
	return false;
}

/* string only methods */
private_fun void String_setText(void* obj, const char* text)
{
	CAST(String, obj, , );
	FREE(self->str);
	self->str = basic_strcpy(text);
	self->length = basic_strlen(text);
}

private_fun char String_charAt(void* obj, size_t index)
{
	CAST(String, obj, 0, );
	if (index < 0) return 0;
	if (index >= self->length) return 0;
	return *(self->str + index);
}

private_fun String* String_stringAt(void* obj, size_t index);
private_fun String* String_subString(void* obj, size_t start, size_t end);
private_fun size_t String_length(void* obj)
{
	CAST(String, obj, -1, );
	return self->length;
}

private_fun void String_toLowerCase(void* obj);
private_fun void String_toUpperCase(void* obj);

private_fun boolean String_containsChar(void* obj, char c)
{
	return String_containsCharOffset(obj, c, 0);
}

private_fun boolean String_containsCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, false, );
	if (offset < 0) return false;
	if (offset >= self->length) return false;
	for (size_t i = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) return true;
	}
	return false;
}

private_fun size_t String_findFirstChar(void* obj, char c)
{
	return String_findFirstCharOffset(obj, c, 0);
}
private_fun size_t String_findLastChar(void* obj, char c)
{
	return String_findLastCharOffset(obj, c, 0);
}
private_fun size_t String_findLastCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, -1, );
	if (offset < 0) return -1;
	if (offset >= self->length) return -1;
	if (!String_containsCharOffset(obj, c, offset)) return -1;
	size_t j = 0;
	for (size_t i = self->length; i <= offset; --i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) j = i;
	}
	return j;
}
private_fun size_t String_findFirstCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, -1, );
	if (offset < 0) return -1;
	if (offset >= self->length) return -1;
	if (!String_containsCharOffset(obj, c, offset)) return -1;
	size_t j = 0;
	for (size_t i = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) j = i;
	}
	return j;
}

private_fun void String_replaceAllChar(void* obj, char old, char new)
{
	String_replaceAllCharOffset(obj, old, new, 0);
}

private_fun void String_replaceFirstChar(void* obj, char old, char new)
{
	String_replaceFirstCharOffset(obj, old, new, 0);
}

private_fun void String_replaceLastChar(void* obj, char old, char new)
{
	String_replaceLastCharOffset(obj, old, new, 0);
}
private_fun void String_replaceAllCharOffset(void* obj, char old, char new, size_t offset)
{
	CAST(String, obj, , );
	if (offset < 0) return;
	if (offset >= self->length) return;
	if (!String_containsCharOffset(obj, old, offset)) return;
	for (size_t i = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), old, false)) basic_memset(self->str + i, new, 1);
	}
}
private_fun void String_replaceFirstCharOffset(void* obj, char old, char new, size_t offset)
{
	CAST(String, obj, , );
	size_t index = String_findFirstCharOffset(obj, old, 0);
	if (index >= self->length) return;
	basic_memset(self->str + index, new, 1);
}

private_fun void String_replaceLastCharOffset(void* obj, char old, char new, size_t offset)
{
	CAST(String, obj, , );
	size_t index = String_findLastCharOffset(obj, old, 0);
	if (index >= self->length) return;
	basic_memset(self->str + index, new, 1);
}

private_fun boolean String_containsSubstring(void* obj, void* str)
{
	String_containsSubstringOffset(obj, str, 0);
}
private_fun boolean String_containsSubstringOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, false, );
	CAST(String, str, false, 1);

	if (offset >= self->length) return false;
	if (self1->length > self->length) return false;
	for (size_t i = offset, j = 0; i < self->length; ++i) {
		if (String_charAt(obj, i) == String_charAt(str, 0)) {
			for (j = 0; j < self1->length; ++j) {
				if (!String_cmpChar(String_charAt(obj, i + j), String_charAt(str, j), false)) {
					i += j;
					break;
				}
			}
			if (j == self1->length - 1) return true;
		}
	}
	return false;
}

private_fun size_t String_findFirstString(void* obj, void* str)
{
	return String_findFirstStringOffset(obj, str, 0);
}
private_fun size_t String_findLastString(void* obj, void* str)
{
	return String_findLastStringOffset(obj, str, 0);
}
private_fun size_t String_findLastStringOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, -1, );
	CAST(String, obj, -1, 1);
	if (offset >= self->length) return -1;
	if (self1->length > self->length) return -1;

	for (size_t i = self->length - 1, j = 0; i >= offset; --i) {
		if (String_charAt(obj, i) == String_charAt(str, self1->length - 1)) {
			for (j = self1->length - 1; j >= 0; --j) {
				if (!String_cmpChar(String_charAt(obj, i), String_charAt(str, j), false)) break;
				if (j == 0) return i;
				--i;
			}
		}
	}
	return -1;
}

private_fun size_t String_findFirstStringOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, -1, );
	CAST(String, obj, -1, 1);
	if (offset >= self->length) return -1;
	if (self1->length > self->length) return -1;

	for (size_t i = offset, j = 0; i < self->length; ++i) {
		if (String_charAt(obj, i) == String_charAt(str, 0)) {
			for (j = 0; j < self1->length; ++j) {
				if (!String_cmpChar(String_charAt(obj, i + j), String_charAt(str, j), false)) {
					i += j;
					break;
				}
			}
			if (j == self1->length - 1) return i;
		}
	}
	return -1;
}
private_fun Array* String_findAllSubstrings(void* obj, void* str);
private_fun Array* String_findAllSubstringsOffset(void* obj, void* str, size_t offset);
private_fun Array* String_split(void* obj, void* str);
private_fun void String_replaceAllSubstring(void* obj, void* sub);
private_fun void String_replaceFirstSubstring(void* obj, void* sub);
private_fun void String_replaceLastSubstring(void* obj, void* sub);
private_fun void String_replaceAllSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_replaceFirstSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_replaceLastSubstringOffset(void* obj, void* sub, size_t offset);

private_fun boolean String_compare(void* obj, void* str2);
private_fun boolean String_compareIgnCase(void* obj, void* str2);
private_fun boolean Stringis_Empty(void* obj);

private_fun void String_append(void* str1, void* str2);
private_fun void String_trim(void* obj);

private_fun String* String_doubleToString(double value);
private_fun String* String_floatToString(float value);
private_fun String* String_intToString(int value);
private_fun String* String_size_tToString(size_t value);

private_fun double String_parseDouble(void* obj);
private_fun float String_parseFloat(void* obj);
private_fun int String_parseInt(void* obj);
private_fun size_t String_parseSize_t(void* obj);

/* Helper functions */
private_fun boolean String_cmpChar(char a, char b, boolean ignCase)
{
	if (a == b) return true;
	if (ignCase) {
		char c = String_CharToLower(a);
		char d = String_CharToLower(b);
		if (c == d) return true;
		else return false;
	}
	else return false;
}

private_fun char String_CharToLower(char a) 
{
	if (a >= 97 && a < 122) {
		return a - 32;
	}
	else return a;
}