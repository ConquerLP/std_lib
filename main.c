#include "std_lib.h"

int main(void) {

	String* str = String_ctor("test");

	if (_containsS(str, "test"));
	if (_compareS(str, "train"));


	PRINT_DEBUG_MEMORY;

	return 0;
}