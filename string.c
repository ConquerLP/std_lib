#include "string.h"
#include "string.r"

#include "def.h"
#include "basic.h"

#include "object.h"
#include "object.r"

/* function prototypes */
private_fun char* String_toString(void* obj);
private_fun void* String_clone(void* obj);
private_fun void String_dtor(void* obj);
private_fun boolean String_equals(void* obj, void* obj2);

private_fun void String_setText(void* obj, const char* text);

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
}