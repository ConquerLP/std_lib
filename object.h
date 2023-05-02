#ifndef OBJECT_H

#define OBJECT_H

typedef struct _ObjectIF {
	char* (*toString)(void* obj);
	void* (*clone)(void* obj);
	void (*dtor)(void* obj);
}ObjectIF;

typedef struct _Object {
	void* self;
	ObjectIF* objectIF;
}Object;

#endif // !OBJECT_H