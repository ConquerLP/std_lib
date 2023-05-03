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
	if (!obj) return;
	String* this = obj;
	o_String* self = this->self;

	FREE(this->stringIF);
	FREE(self->str);

	Object* tmp = Object_ctor("");
	tmp->objectIF->dtor(this->super);
	tmp->objectIF->dtor(tmp);

	FREE(self);
	FREE(this);
}

private_fun char* String_toString(void* obj)
{
	if (!obj) return NULL;
	String* this = obj;
	return ((o_String*)this->self)->str;
}

private_fun void* String_clone(void* obj)
{
	if (!obj) return NULL;
	String* this = obj;
	String* new = String_ctor(((o_String*)this->self)->str);
	return new;
}

/* string only methods */
private_fun void String_setText(void* obj, const char* text)
{
	if (!obj) return;
	String* this = obj;
	o_String* self = this->self;
	FREE(self->str);
	self->str = basic_strcpy(text);
}