#include "std_lib.h"

int main(void) {

	String* str = String_ctor("boo:and:foo");

	String* regex = String_ctor("o");

	Array* arr = str->stringIF->split(str, regex);

	for (size_t i = 0; i < arr->arrayIF->length(arr); ++i) {
		String* tmp = arr->arrayIF->get(arr, i);
		printf("%s", tmp->objectIF->toString(tmp));
	}

	delete(str);
	delete(regex);
	delete(arr);

	PRINT_DEBUG_MEMORY;

	return 0;
}