#include "std_lib.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	String* s = String_ctor("text");
	s->stringIF->setText(s, "test");

	String* s1 = s->objectIF->clone(s);
	s1->stringIF->setText(s1, "ficken");

	Array* a = Array_ctor("String", 20);

	double b = 4.0;

	for (size_t i = 0; i < a->arrayIF->length(a); ++i) {
		a->arrayIF->set(a, s, i);
		String* ss = (String*)a->arrayIF->get(a, i);
		printf("%s\n", ss->objectIF->toString(ss));
	}
	
	Array* aa = a->objectIF->clone(a);

	printf("%zu\n", sizeof(String));

	printf("%s\n", s->objectIF->toString(s));
	printf("%s\n", s1->objectIF->toString(s1));


	s->objectIF->dtor(s);
	s1->objectIF->dtor(s1);
	a->objectIF->dtor(a);
	aa->objectIF->dtor(aa);
	
	PRINT_DEBUG_MEMORY;

	return 0;
}