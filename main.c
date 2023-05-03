#include "std_lib.h"

int main(void) {

	Array* a = Array_ctor("String", 100);
	String* str = String_ctor("test");

	String* s1 = s->objectIF->clone(s);
	s1->stringIF->setText(s1, "ficken");

	Array* a = Array_ctor("String", 20);

	double b = 4.0;

	for (size_t i = 0; i < a->arrayIF->length(a); ++i) {
		a->arrayIF->set(a, s, i);
		String* ss = a->arrayIF->get(a, i);
		printf("%s\n", ss->objectIF->toString(ss));
	}

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

	return 0;
}