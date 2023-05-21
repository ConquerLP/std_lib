#include "std_lib.h"

int main(void) {

	String* str = String_ctor("Test");

	str->stringIF->insertCharAt(str, ' ', 0);

	delete(str);

	PRINT_DEBUG_MEMORY;

	return 0;
}