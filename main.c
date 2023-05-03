#include "std_lib.h"

int main(void) {

	Array* a = Array_ctor("String", 100);
	String* str = String_ctor("test");

	for (size_t i = 0; i < a->arrayIF->length(a); ++i) {
		a->arrayIF->set(a, str, i);
		String* tmp = a->arrayIF->get(a, i);
		printf("%s\n", tmp->objectIF->toString(tmp));
	}

	delete(a);
	delete(str);

	PRINT_DEBUG_MEMORY;

	return 0;
}