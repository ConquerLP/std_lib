#include "std_lib.h"

int main(void) {

	String* str = String_ctor("boo:and:foo");

	Array* test = Array_ctor("String", 20);
	test->arrayIF->fill(test, str);


	String* str1 = String_join(test);

	printf("\n%s\n", str1->objectIF->toString(str1));

	delete(str);
	delete(str1);
	delete(test);

	PRINT_DEBUG_MEMORY;

	return 0;
}