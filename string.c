#include "string.h"
#include "string.r"

#include "array.h"
#include "array.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

#define TMP_CHAR_LENGTH 20

/* function prototypes */
/* Helper functions*/
private_fun boolean String_cmpChar(char a, char b, boolean ignCase);
private_fun char String_CharToLower(char a);
private_fun char String_CharToUpper(char a);

/* overriding methods */
private_fun char* String_toString(void* obj);
private_fun void* String_clone(void* obj);
private_fun void String_dtor(void* obj);
private_fun boolean String_equals(void* obj, void* obj2);

/* methods */
private_fun void String_setText(void* obj, const char* text);
private_fun char String_charAt(void* obj, size_t index);

private_fun size_t String_length(void* obj);
private_fun void String_toLowerCase(void* obj);
private_fun void String_toUpperCase(void* obj);

private_fun boolean String_containsChar(void* obj, char c);
private_fun boolean String_containsCharOffset(void* obj, char c, size_t offset);
private_fun size_t String_countOccurencesChar(void* obj, char c);
private_fun size_t String_countOccurencesCharOffset(void* obj, char c, size_t offset);
private_fun size_t String_findFirstChar(void* obj, char c);
private_fun size_t String_findLastChar(void* obj, char c);
private_fun size_t String_findLastCharOffset(void* obj, char c, size_t offset);
private_fun size_t String_findFirstCharOffset(void* obj, char c, size_t offset);
private_fun Array* String_findAllChar(void* obj, char c);
private_fun Array* String_findAllCharOffset(void* obj, char c, size_t offset);

private_fun void String_replaceAllChar(void* obj, char old, char new);
private_fun void String_replaceFirstChar(void* obj, char old, char new);
private_fun void String_replaceLastChar(void* obj, char old, char new);
private_fun void String_replaceAllCharOffset(void* obj, char old, char new, size_t offset);
private_fun void String_replaceFirstCharOffset(void* obj, char old, char new, size_t offset);
private_fun void String_replaceLastCharOffset(void* obj, char old, char new, size_t offset);

private_fun void String_removeAllChar(void* obj, char old);
private_fun void String_removeFirstChar(void* obj, char old);
private_fun void String_removeLastChar(void* obj, char old);
private_fun void String_removeAllCharOffset(void* obj, char old, size_t offset);
private_fun void String_removeFirstCharOffset(void* obj, char old, size_t offset);
private_fun void String_removeLastCharOffset(void* obj, char old, size_t offset);

private_fun boolean String_containsSubstring(void* obj, void* str);
private_fun boolean String_containsSubstringOffset(void* obj, void* str, size_t offset);
private_fun size_t String_countSubstringOccurences(void* obj, void* str);
private_fun size_t String_countSubstringOccurencesOffset(void* obj, void* str, size_t offset);
private_fun size_t String_findFirstString(void* obj, void* str);
private_fun size_t String_findLastString(void* obj, void* str);
private_fun size_t String_findLastStringOffset(void* obj, void* str, size_t offset);
private_fun size_t String_findFirstStringOffset(void* obj, void* str, size_t offset);
private_fun Array* String_findAllSubstrings(void* obj, void* str);
private_fun Array* String_findAllSubstringsOffset(void* obj, void* str, size_t offset);
//private_fun Array* String_split(void* obj, void* str);

private_fun void String_replaceAllSubstring(void* obj, void* sub, void* replacement);
private_fun void String_replaceFirstSubstring(void* obj, void* sub, void* replacement);
private_fun void String_replaceLastSubstring(void* obj, void* sub, void* replacement);
private_fun void String_replaceAllSubstringOffset(void* obj, void* sub, void* replacement, size_t offset);
private_fun void String_replaceFirstSubstringOffset(void* obj, void* sub, void* replacement, size_t offset);
private_fun void String_replaceLastSubstringOffset(void* obj, void* sub, void* replacement, size_t offset);

private_fun void String_removeAllSubstring(void* obj, void* sub);
private_fun void String_removeFirstSubstring(void* obj, void* sub);
private_fun void String_removeLastSubstring(void* obj, void* sub);
private_fun void String_removeAllSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_removeFirstSubstringOffset(void* obj, void* sub, size_t offset);
private_fun void String_removeLastSubstringOffset(void* obj, void* sub, size_t offset);

private_fun boolean String_compare(void* obj, void* str2);
private_fun boolean String_compareIgnCase(void* obj, void* str2);
private_fun boolean String_isEmpty(void* obj);

private_fun void String_append(void* str1, void* str2);
private_fun void String_trim(void* obj, const char* toTrim);

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

	((o_Object*)super->self)->sub = this;
	this->super = super; 
	this->self = self; 
	this->stringIF = thisIF; 
	this->objectIF = super->objectIF; 

	super->objectIF->toString = &String_toString;
	super->objectIF->clone = &String_clone;
	super->objectIF->dtor = &String_dtor;
	super->objectIF->equals = &String_equals;

	thisIF->setText = &String_setText;

	thisIF->charAt = &String_charAt;
	thisIF->stringAt = &String_stringAt;
	thisIF->substring = &String_subString;
	thisIF->length = &String_length;
	thisIF->toLowerCase = &String_toLowerCase;
	thisIF->toUpperCase = &String_toUpperCase;

	thisIF->containsChar = &String_containsChar;
	thisIF->containsCharOffset = &String_containsCharOffset;
	thisIF->countOccurencesChar = &String_countOccurencesChar;
	thisIF->countOccurencesCharOffset = &String_countOccurencesCharOffset;
	thisIF->findFirstChar = &String_findFirstChar;
	thisIF->findLastChar = &String_findLastChar;
	thisIF->findLastCharOffset = &String_findLastCharOffset;
	thisIF->findFirstCharOffset = &String_findFirstCharOffset;
	thisIF->findAllChar = &String_findAllChar;
	thisIF->findAllCharOffset = &String_findAllCharOffset;

	thisIF->replaceAllChar = &String_replaceAllChar;
	thisIF->replaceFirstChar = &String_replaceFirstChar;
	thisIF->replaceLastChar = &String_replaceLastChar;
	thisIF->replaceAllCharOffset = &String_replaceAllCharOffset;
	thisIF->replaceFirstCharOffset = &String_replaceFirstCharOffset;
	thisIF->replaceLastCharOffset = &String_replaceLastCharOffset;

	thisIF->removeAllChar = &String_removeAllChar;
	thisIF->removeFirstChar = &String_removeFirstChar;
	thisIF->removeLastChar = &String_removeLastChar;
	thisIF->removeAllCharOffset = &String_removeAllCharOffset;
	thisIF->removeFirstCharOffset = &String_removeFirstCharOffset;
	thisIF->removeLastCharOffset = &String_removeLastCharOffset;

	thisIF->containsSubstring = &String_containsSubstring;
	thisIF->containsSubstringOffset = &String_containsSubstringOffset;
	thisIF->countSubstringOccurences = &String_countSubstringOccurences;
	thisIF->countSubstringOccurencesOffset = &String_countSubstringOccurencesOffset;
	thisIF->findFirstString = &String_findFirstString;
	thisIF->findLastString = &String_findLastString;
	thisIF->findLastStringOffset = &String_findLastStringOffset;
	thisIF->findFirstStringOffset = &String_findFirstStringOffset;
	thisIF->findAllSubstrings = &String_findAllSubstrings;
	thisIF->findAllSubstringsOffset = &String_findAllSubstringsOffset;
	//thisIF->split = &String_split;

	thisIF->replaceAllSubstring = &String_replaceAllSubstring;
	thisIF->replaceFirstSubstring = &String_replaceFirstSubstring;
	thisIF->replaceLastSubstring = &String_replaceLastSubstring;
	thisIF->replaceAllSubstringOffset = &String_replaceAllSubstringOffset;
	thisIF->replaceFirstSubstringOffset = &String_replaceFirstSubstringOffset;
	thisIF->replaceLastSubstringOffset = &String_replaceLastSubstringOffset;

	thisIF->removeAllSubstring = &String_removeAllSubstring;
	thisIF->removeFirstSubstring = &String_removeFirstSubstring;
	thisIF->removeLastSubstring = &String_removeLastSubstring;
	thisIF->removeAllSubstringOffset = &String_removeAllSubstringOffset;
	thisIF->removeFirstSubstringOffset = &String_removeFirstSubstringOffset;
	thisIF->removeLastSubstringOffset = &String_removeLastSubstringOffset;

	thisIF->compare = &String_compare;
	thisIF->compareIgnCase = &String_compareIgnCase;
	thisIF->isEmpty = &String_isEmpty;

	thisIF->append = &String_append;
	thisIF->trim = &String_trim;

	thisIF->doubleToString = &String_doubleToString;
	thisIF->floatToString = &String_floatToString;
	thisIF->intToString = &String_intToString;
	thisIF->size_tToString = &String_size_tToString;

	thisIF->parseDouble = &String_parseDouble;
	thisIF->parseFloat = &String_parseFloat;
	thisIF->parseInt = &String_parseInt;
	thisIF->parseSize_t = &String_parseSize_t;
	
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

String* String_stringAt(void* obj, size_t index)
{
	CAST(String, obj, NULL, );
	if (index >= self->length) return NULL;
	return String_subString(obj, index, self->length - 1);
}
String* String_subString(void* obj, size_t start, size_t end)
{
	CAST(String, obj, NULL, );
	if (self->length <= 0) return NULL;
	if (start > end) return NULL;
	if (end >= self->length) return NULL;
	if (start >= self->length) return NULL;
	String* sub = String_ctor("0");
	if (end == start) {
		String_replaceFirstChar(sub, '0', String_charAt(obj, start));
		return sub;
	}
	CAST(String, sub, NULL, 1);
	size_t sub_length = end - start + 1;
	self1->length = sub_length;
	FREE(self1->str);
	char* tmp;
	MALLOC(char, sub_length, tmp);
	basic_bin_copy(tmp, self->str + start, sub_length, 0);
	basic_memset(tmp + sub_length - 1, '\0', 1);
	self1->str = tmp;
	return sub;
}

private_fun size_t String_length(void* obj)
{
	CAST(String, obj, -1, );
	return self->length;
}

private_fun void String_toLowerCase(void* obj)
{
	CAST(String, obj, , );
	for (size_t i = 0; i < self->length; ++i) {
		basic_memset(self->str + i, String_CharToLower(String_charAt(this, i)), 1);
	}
}

private_fun void String_toUpperCase(void* obj)
{
	CAST(String, obj, , );
	for (size_t i = 0; i < self->length; ++i) {
		basic_memset(self->str + i, String_CharToUpper(String_charAt(this, i)) , 1);
	}
}

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

private_fun size_t String_countOccurencesChar(void* obj, char c)
{
	return String_countOccurencesCharOffset(obj, c, 0);
}

private_fun size_t String_countOccurencesCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, -1, );
	if (offset >= self->length) return -1;
	size_t count = 0;
	for (size_t i = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) count++;
	}
	return count;
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
	for (size_t i = self->length - 1; i >= offset; --i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) return i;
	}
	return -1;
}
private_fun size_t String_findFirstCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, -1, );
	if (offset < 0) return -1;
	if (offset >= self->length) return -1;
	if (!String_containsCharOffset(obj, c, offset)) return -1;
	for (size_t i = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) return i;
	}
	return -1;
}

private_fun Array* String_findAllChar(void* obj, char c)
{
	return String_findAllCharOffset(obj, c, 0);
}

private_fun Array* String_findAllCharOffset(void* obj, char c, size_t offset)
{
	CAST(String, obj, NULL, );
	if (offset < 0) return NULL;
	if (offset >= self->length) return NULL;
	size_t count = String_countOccurencesCharOffset(obj, c, offset);
	if (count == 0) return NULL;
	Array* arr = Array_ctor("size_t", count);
	size_t* tmp;
	MALLOC(size_t, 1, tmp);
	*tmp = 0;
	for (size_t i = offset, j = 0; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), c, false)) {
			*tmp = i;
			arr->arrayIF->set(arr, tmp, j);
			j++;
		}
	}
	FREE(tmp);
	return arr;
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
	size_t index = String_findFirstCharOffset(obj, old, offset);
	if (index >= self->length) return;
	basic_memset(self->str + index, new, 1);
}

private_fun void String_replaceLastCharOffset(void* obj, char old, char new, size_t offset)
{
	CAST(String, obj, , );
	size_t index = String_findLastCharOffset(obj, old, offset);
	if (index >= self->length) return;
	basic_memset(self->str + index, new, 1);
}

private_fun void String_removeAllChar(void* obj, char old)
{
	String_removeAllCharOffset(obj, old, 0);
}

private_fun void String_removeFirstChar(void* obj, char old)
{
	String_removeFirstCharOffset(obj, old, 0);
}

private_fun void String_removeLastChar(void* obj, char old)
{
	String_removeFirstCharOffset(obj, old, 0);
}

private_fun void String_removeAllCharOffset(void* obj, char old, size_t offset)
{
	CAST(String, obj, , );
	if (offset >= self->length) return;
	if (offset < 0) return;
	if (self->length == 0) return;
	size_t count = 0;
	char* tmp;
	MALLOC(char, self->length, tmp);
	basic_bin_copy(tmp, self->str, offset, 0);
	for (size_t i = offset, j = offset; i < self->length; ++i) {
		if (String_cmpChar(String_charAt(this, i), old, false)) {
			count++;
			continue;
		}
		basic_memset(tmp + j, String_charAt(obj, i), 1);
		++j;
	}
	REALLOC(char, self->length - count, tmp);
	self->length -= count;
	FREE(self->str);
	self->str = tmp;
}

private_fun void String_removeFirstCharOffset(void* obj, char old, size_t offset)
{
	CAST(String, obj, , );
	if (offset >= self->length) return;
	if (offset < 0) return;
	if (self->length == 0) return;
	size_t index = String_findFirstCharOffset(obj, old, offset);
	if (index >= self->length) return;
	String* part1 = String_subString(obj, 0, index);
	String* part2 = String_stringAt(obj, index + 1);
	String_append(part1, part2);
	String_setText(obj, part1->objectIF->toString(part1));
	delete(part1);
	delete(part2);
}

private_fun void String_removeLastCharOffset(void* obj, char old, size_t offset)
{
	CAST(String, obj, , );
	if (offset >= self->length) return;
	if (offset < 0) return;
	if (self->length == 0) return;
	size_t index = String_findLastCharOffset(obj, old, offset);
	if (index >= self->length) return;
	String* part1 = String_subString(obj, 0, index);
	String* part2 = String_stringAt(obj, index + 1);
	String_append(part1, part2);
	String_setText(obj, part1->objectIF->toString(part1));
	delete(part1);
	delete(part2);
}

private_fun boolean String_containsSubstring(void* obj, void* str)
{
	return String_containsSubstringOffset(obj, str, 0);
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

private_fun size_t String_countSubstringOccurences(void* obj, void* str)
{
	return String_countSubstringOccurencesOffset(obj, str, 0);
}

private_fun size_t String_countSubstringOccurencesOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, -1, );
	CAST(String, str, -1, 1);
	if (offset >= self->length) return -1;
	if (self1->length > self->length) return -1;
	size_t count = 0;
	size_t index = 0;
	while (1) {
		index = String_findFirstStringOffset(obj, str, offset);
		if (index >= self->length) break;
		offset = index + self1->length - 1;
		count++;
	}
	return count;
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
	CAST(String, str, -1, 1);
	if (offset >= self->length) return -1;
	if (self1->length > self->length) return -1;
	for (size_t i = self->length - 2, j = 0; i >= offset; --i) {
		if (String_charAt(obj, i) == String_charAt(str, self1->length - 2)) {
			for (j = self1->length - 2; j >= 0; --j) {
				if (!String_cmpChar(String_charAt(obj, i), String_charAt(str, j), false)) break;
				if (j == 0) {
					if (i < offset) return -1;
					else return i;
				} 
				--i;
			}
		}
	}
	return -1;
}

private_fun size_t String_findFirstStringOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, -1, );
	CAST(String, str, -1, 1);
	if (offset >= self->length) return -1;
	if (self1->length > self->length) return -1;
	for (size_t i = offset, j = 0; i < self->length; ++i) {
		if (String_charAt(obj, i) == String_charAt(str, 0)) {
			for (j = 0; j < self1->length - 1; ++j) {
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

private_fun Array* String_findAllSubstrings(void* obj, void* str)
{
	return String_findAllSubstringsOffset(obj, str, 0);
}

private_fun Array* String_findAllSubstringsOffset(void* obj, void* str, size_t offset)
{
	CAST(String, obj, NULL, );
	CAST(String, str, NULL, 1);
	size_t count = String_countSubstringOccurencesOffset(obj, str, offset);
	if (count == 0) return NULL;
	Array* arr = Array_ctor("size_t", count);
	size_t index = 0;
	for (size_t i = 0; i < count; ++i) {
		index = String_findFirstStringOffset(obj, str, offset);
		if (index >= self->length) break;
		offset = index + self1->length - 1;
		arr->arrayIF->set(arr, &index, i);
	}
	return arr;
}

/*
private_fun Array* String_split(void* obj, void* str)
{
	CAST(String, obj, NULL, );
	CAST(String, str, NULL, 1);
}
*/

private_fun void String_replaceAllSubstring(void* obj, void* sub, void* replacement)
{
	String_replaceAllSubstringOffset(obj, sub, replacement, 0);
}

private_fun void String_replaceFirstSubstring(void* obj, void* sub, void* replacement)
{
	String_replaceFirstSubstringOffset(obj, sub, replacement, 0);
}

private_fun void String_replaceLastSubstring(void* obj, void* sub, void* replacement)
{
	String_replaceLastSubstringOffset(obj, sub, replacement, 0);
}

private_fun void String_replaceAllSubstringOffset(void* obj, void* sub, void* replacement, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	CAST(String, replacement, , 2);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	long long int new_length_inc = self2->length - self1->length;
	size_t index = String_findFirstStringOffset(obj, sub, offset);
	if (index >= self->length) return;
	size_t count = String_countSubstringOccurencesOffset(obj, sub, offset);
	if (new_length_inc == 0) {
		for (size_t i = 0; i < count; ++i) {
			basic_bin_copy(self->str, self2->str, self2->length - 1, index);
			index = String_findFirstStringOffset(obj, sub, index + self1->length - 1);
		}
		return;
	}
	char* tmp;
	size_t new_length = count * new_length_inc + self->length;
	MALLOC(char, new_length, tmp);
	basic_memset(tmp + new_length - 1, '\0', 1);
	basic_bin_copy(tmp, self->str, offset, 0);
	size_t i = offset;
	size_t j = offset;
	while (i < self->length - 1) {
		if (i == index) {
			index = String_findFirstStringOffset(obj, sub, index + self1->length - 1);
			basic_bin_copy(tmp, self2->str, self2->length - 1, j);
			j += self2->length - 1;
			i += self1->length - 1;
		}
		else {
			basic_memset(tmp + j, String_charAt(obj, i), 1);
			i++;
			j++;
		}
	}
	FREE(self->str);
	self->str = tmp;
	self->length = new_length;
}

private_fun void String_replaceFirstSubstringOffset(void* obj, void* sub, void* replacement, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	CAST(String, replacement, , 2);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	size_t new_length_inc = self2->length - self1->length;
	size_t new_length = self->length + new_length_inc;
	size_t index = String_findFirstStringOffset(obj, sub, offset);
	if (index >= self->length) return;
	char* tmp;
	MALLOC(char, new_length, tmp);
	basic_bin_copy(tmp, self->str, index, 0);
	basic_bin_copy(tmp, self2->str, self2->length - 1, index);
	basic_bin_copy(tmp, self->str + index + self1->length - 1, self->length - index - self1->length + 1, index + self2->length - 1);
	FREE(self->str);
	self->length = new_length;
	self->str = tmp;
}

private_fun void String_replaceLastSubstringOffset(void* obj, void* sub, void* replacement, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	CAST(String, replacement, , 2);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	size_t new_length_inc = self2->length - self1->length;
	size_t new_length = self->length + new_length_inc;
	size_t index = String_findLastStringOffset(obj, sub, offset);
	if (index >= self->length) return;
	char* tmp;
	MALLOC(char, new_length, tmp);
	basic_bin_copy(tmp, self->str, index, 0);
	basic_bin_copy(tmp, self2->str, self2->length - 1, index);
	basic_bin_copy(tmp, self->str + index + self1->length - 1, self->length - index - self1->length + 1, index + self2->length - 1);
	FREE(self->str);
	self->length = new_length;
	self->str = tmp;
}

private_fun void String_removeAllSubstring(void* obj, void* sub)
{
	String_removeAllSubstringOffset(obj, sub, 0);
}

private_fun void String_removeFirstSubstring(void* obj, void* sub)
{
	String_removeFirstSubstringOffset(obj, sub, 0);
}

private_fun void String_removeLastSubstring(void* obj, void* sub)
{
	String_removeLastSubstringOffset(obj, sub, 0);
}

private_fun void String_removeAllSubstringOffset(void* obj, void* sub, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	if (self1->length == self->length && offset == 0) {
		self->length = 0;
		FREE(self->str);
		self->str = basic_strcpy("");
		return;
	}
	size_t count = String_countSubstringOccurencesOffset(obj, sub, offset);
	if (count == 0) return;
	size_t new_size = (-1) * (self1->length - 1) * count + self->length;
	char* tmp;
	MALLOC(char, new_size, tmp);
	size_t i = offset;
	size_t j = offset;
	basic_bin_copy(tmp, self->str, offset, 0);
	basic_memset(tmp + new_size - 1, '\0', 1);
	size_t index = String_findFirstStringOffset(obj, sub, offset);
	while (i < self->length - 1) {
		if (i == index) {
			index = String_findFirstStringOffset(obj, sub, index + self1->length - 1);
			i += self1->length - 1;
		}
		else {
			basic_memset(tmp + j, String_charAt(obj, i), 1);
			i++;
			j++;
		}
	}
	FREE(self->str);
	self->str = tmp;
	self->length = new_size;
}

private_fun void String_removeFirstSubstringOffset(void* obj, void* sub, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	size_t index = String_findFirstStringOffset(obj, sub, offset);
	if (index >= self->length) return;
	size_t new_size = self->length - self1->length + 1;
	char* tmp;
	MALLOC(char, new_size, tmp);
	basic_memset(tmp + new_size - 1, '\0', 1);
	basic_bin_copy(tmp, self->str, index, 0);
	basic_bin_copy(tmp, self->str + index + self1->length - 1, self->length - index - self1->length + 1, index);
	FREE(self->str);
	self->length = new_size;
	self->str = tmp;
}

private_fun void String_removeLastSubstringOffset(void* obj, void* sub, size_t offset)
{
	CAST(String, obj, , );
	CAST(String, sub, , 1);
	if (offset >= self->length) return;
	if (self1->length > self->length) return;
	size_t index = String_findLastStringOffset(obj, sub, offset);
	if (index >= self->length) return;
	size_t new_size = self->length - self1->length + 1;
	char* tmp;
	MALLOC(char, new_size, tmp);
	basic_memset(tmp + new_size - 1, '\0', 1);
	basic_bin_copy(tmp, self->str, index, 0);
	basic_bin_copy(tmp, self->str + index + self1->length - 1, self->length - index - self1->length + 1, index);
	FREE(self->str);
	self->length = new_size;
	self->str = tmp;
}

private_fun boolean String_compare(void* obj, void* str2)
{
	CAST(String, obj, false, );
	CAST(String, str2, false, 1);
	return basic_strcmp(self->str, self1->str);
}

private_fun boolean String_compareIgnCase(void* obj, void* str2)
{
	CAST(String, obj, false, );
	CAST(String, str2, false, 1);

	return basic_strcmpIgnCase(self->str, self1->str);
}

private_fun boolean String_isEmpty(void* obj)
{
	CAST(String, obj, true, );
	if (self->length <= 1) return true;
	else return false;
}

private_fun void String_append(void* str1, void* str2)
{
	CAST(String, str1, , );
	CAST(String, str2, , 1);
	size_t new_length = self->length + self1->length - 1;
	self->length = new_length;
	char* copy_str1 = basic_strcpy(self->str);
	FREE(self->str);
	char* self_str;
	MALLOC(char, new_length, self_str);
	basic_bin_copy(self_str, copy_str1, basic_strlen(copy_str1) - 1, 0);
	basic_bin_copy(self_str, self1->str, self1->length, basic_strlen(copy_str1) - 1);
	FREE(copy_str1);
	self->str = self_str;
}

private_fun void String_trim(void* obj, const char* toTrim)
{
	for (size_t i = 0; i < basic_strlen(toTrim) - 1; ++i) {
		String_removeAllChar(obj, toTrim[i]);
	}
}

String* String_doubleToString(double value)
{
	char buff[TMP_CHAR_LENGTH] = { 0 };
	snprintf(buff, TMP_CHAR_LENGTH - 1, "%lf", value);
	String* string = String_ctor(buff);
	String_trim(string, " ");
	return string;
}

String* String_floatToString(float value)
{
	char buff[TMP_CHAR_LENGTH] = { 0 };
	snprintf(buff, TMP_CHAR_LENGTH - 1, "%f", value);
	String* string = String_ctor(buff);
	String_trim(string, "\0 ");
	return string;
}

String* String_intToString(int value) 
{
	char buff[TMP_CHAR_LENGTH] = { 0 };
	snprintf(buff, TMP_CHAR_LENGTH - 1, "%i", value);
	String* string = String_ctor(buff);
	String_trim(string, "\0 ");
	return string;
}

String* String_size_tToString(size_t value)
{
	char buff[TMP_CHAR_LENGTH] = { 0 };
	snprintf(buff, TMP_CHAR_LENGTH - 1, "%zu", value);
	String* string = String_ctor(buff);
	String_trim(string, "\0 ");
	return string;
}

private_fun double String_parseDouble(void* obj)
{
	CAST(String, obj, 0.0, );
	char to_check[] = { "\t\n/*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmlnopqrstuvwxyz" };
	for (size_t i = 0; i < basic_strlen(to_check) - 1; ++i) {
		if (String_containsChar(obj, to_check[i])) return 0.0;
	}
	char check_doubles[] = { "-+." };
	for (size_t i = 0; i < basic_strlen(check_doubles) - 1; ++i) {
		if (String_countOccurencesChar(obj, check_doubles[i]) > 1) return 0.0;
	}
	if (String_containsChar(obj, '+') && String_containsChar(obj, '-')) return 0.0;
	String* filter = String_ctor("");
	String* filter_repalcement = String_ctor("");
	if (String_charAt(obj, 0) == '-' && String_charAt(obj, 1) == '.') {
		String_setText(filter, "-.");
		String_setText(filter_repalcement, "-0.");
		String_replaceFirstSubstring(obj, filter, filter_repalcement);
	}
	if (String_charAt(obj, 0) == '.') {
		String_setText(filter, ".");
		String_setText(filter_repalcement, "0.");
		String_replaceFirstSubstring(obj, filter, filter_repalcement);
	}
	delete(filter);
	delete(filter_repalcement);
	return atof(self->str);
}

private_fun float String_parseFloat(void* obj)
{
	return (float)String_parseDouble(obj);
}

private_fun int String_parseInt(void* obj)
{
	CAST(String, obj, 0, );
	char to_check[] = { "\t\n/*.ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmlnopqrstuvwxyz" };
	for (size_t i = 0; i < basic_strlen(to_check) - 1; ++i) {
		if (String_containsChar(obj, to_check[i])) return 0;
	}
	char check_doubles[] = { "-+" };
	for (size_t i = 0; i < basic_strlen(check_doubles) - 1; ++i) {
		if (String_countOccurencesChar(obj, check_doubles[i]) > 1) return 0;
	}
	if (String_containsChar(obj, '+') && String_containsChar(obj, '-')) return 0;
	return atoi(self->str);
}

private_fun size_t String_parseSize_t(void* obj)
{
	CAST(String, obj, 0, );
	char to_check[] = { "\t\n/*-.ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmlnopqrstuvwxyz" };
	for (size_t i = 0; i < basic_strlen(to_check) - 1; ++i) {
		if (String_containsChar(obj, to_check[i])) return 0;
	}
	char check_doubles[] = { "+" };
	for (size_t i = 0; i < basic_strlen(check_doubles) - 1; ++i) {
		if (String_countOccurencesChar(obj, check_doubles[i]) > 1) return 0;
	}
	String_trim(obj, " +");
	size_t result = 0;
	for (size_t i = 0; i < self->length - 1; ++i) {
		result = result * 10 + (self->str[i] - 48);
	}
	return result;
}

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
	if (a >= 65 && a < 91) {
		return a + 32;
	}
	else return a;
}

private_fun char String_CharToUpper(char a)
{
	if (a >= 97 && a < 123) {
		return a - 32;
	}
	else return a;
}