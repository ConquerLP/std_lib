#include "std_lib.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(void) {

	String* s = String_ctor("text");
	s->stringIF->setText(s, "test");

	String* s1 = s->objectIF->clone(s);
	s1->stringIF->setText(s1, "ficken");

	Array* a = Array_ctor("String", 20);

	double b = 4.0;

	for (size_t i = 0; i < a->arrayIF->length(a); ++i) {
		a->arrayIF->set(a, s, i);
		String* ss = a->arrayIF->get(a, i);
		printf("%s\n", ss->objectIF->toString(ss));
	}

	printf("%zu\n", sizeof(char));
	
	Array* aa = a->objectIF->clone(a);

	printf("%s\n", a->objectIF->toString(a));
	printf("%s\n", a->objectIF->toString(aa));

	printf("%s\n", s->objectIF->toString(s));
	printf("%s\n", s1->objectIF->toString(s1));

	delete(s);
	delete(s1);
	delete(a);
	delete(aa);
	
	PRINT_DEBUG_MEMORY;

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}