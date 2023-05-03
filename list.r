#ifndef LIST_R

#define LIST_R

#include <stdlib.h>

/* List class */

typedef struct _Node {
	struct _Node* prev;
	struct _Node* next;
	void* data;
}Node;

typedef struct _o_List{
	Node* head;
	Node* tail;
	size_t length;
	char* name;
	char* toString;
	void* sub;
}o_List;

#endif