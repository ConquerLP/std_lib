#ifndef TEMPLATE_H

#define TEMPLATE_H

#include "object.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "object.h"
#include <stdlib.h>

typedef struct _ClassIF {
	void (*func)(void);
}ClassIF;

typedef struct _Class {
	void* super; // must be first
	void* self;
	ClassIF* _classIF;
	ObjectIF* o_IF;
}Class;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // TEMPLATE_H
